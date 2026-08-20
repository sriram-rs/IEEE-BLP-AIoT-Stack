# Why This Firmware Is Shaped the Way It Is: The Agentic Architecture Brief

**Audience:** the firmware team taking over `firmware/sim-firmware/`, plus anyone debugging the signal chain from sensor to gateway.
**Read this before changing code.** Several design decisions in this codebase look wrong from a classical embedded perspective and are correct from an agentic one. This document explains the difference so that reviews and changes preserve the intent.

---

## 1. Assistant AI versus agentic AI: the distinction that shapes everything

Most engineers have met AI as a **coding assistant**: you ask a question, it answers; you request a function, it writes one; you paste an error, it explains. In that model the AI is a consultant. The human perceives the world, decides, and acts. The AI only talks.

**Agentic AI inverts this.** An agent is a model given three things:

1. **Perception:** tools that let it read the state of the world for itself (here: live sensor data, sensor metadata, historical series).
2. **Reasoning with agency:** it decides what to look at next. Nobody feeds it a curated dataset; it queries, cross-checks, asks for context, and doubts.
3. **Action under governance:** it can change the world (deploy a control rule, raise an alert, run a calibration dialogue), but only through gated channels a human controls.

The practical consequence for hardware people: **the consumer of your sensor data is no longer a human reading a dashboard. It is a model calling tools.** A human glancing at a chart brings context a chart does not carry: they know the window was open, they know a frozen trace "looks wrong", they know 85.00 °C at power-on is a reset artifact. A model knows none of that unless the system tells it. So the entire system, firmware included, is built to make the world *legible to a machine*:

- Metadata must be machine-readable (the sensor cards).
- Failures must be explicit signals, never plausible-looking numbers.
- Data quality must be measurable from the data itself (sequence counters, monotonic ticks, status bits).
- Physical context the sensors cannot see must have a channel into the system (the deployment journal).

Every one of those is implemented somewhere in the code you now own. Section 4 maps them file by file.

## 2. The system in one picture

```
[Sensor] -> [SIM: ESP32, your firmware] --BLE adv--> [Gateway: Python] --MCP--> [Claude / agents]
             measures, stamps,                        scans, decodes via        perceives via tools,
             flags faults,                            sensor cards, stores,     reasons, validates,
             never interprets                         reconciles time,          authors rules,
                                                      runs approved rules      acts under approval
```

**MCP (Model Context Protocol)**, for those meeting it first here: a standard that lets a model call functions ("tools") exposed by a server, read resources (files, datasheets, the sensor cards), and use prompt templates. The gateway's `mcp_server/` exposes ten tools (`list_sensors`, `describe_sensor`, `read_latest`, `query_timeseries`, `capture_experiment`, `annotate`, `validate_reading`, `deploy_rule`, and experiment helpers). When a student asks Claude "is this room healthy?", Claude discovers the sensors, reads their cards, pulls aligned time series, and answers with evidence. Nobody writes a parser or exports a CSV. That workflow is the product; the dashboard is deliberately a thin bench view.

**The two loops** (this is the single most important architectural idea):

- **Edge loop (cloud unavailable):** the model is a *design-time* tool only. A student states intent in natural language; the agent authors a small deterministic rule (JSON: conditions, thresholds, action); the rule lands as *pending*; a human approves it (`python -m gateway approve-rule`); from then on it runs in `rules/engine.py` with **no model in the path**. A control loop that must survive a dropped link never contains an LLM.
- **Cloud loop (runtime reasoning):** the model operates live through MCP: cross-sensor fusion, long-horizon analysis, natural-language interrogation, watchdog audits. It reads and recommends; any actuation goes back through the gated edge-rule channel.

Firmware sits underneath both loops and serves them identically: it measures honestly and stamps everything. It never needs to know whether a model or a rule consumes the frame.

## 3. The contract chain: why byte layouts are sacred

Agentic systems live or die on **contracts**. A model can write correct code against a typed, documented interface and will confidently write wrong code against an undocumented one. The chain here is:

```
sensor card (gateway/cards/NN_*.json)      <- the authoritative contract
   = payload byte layout + ranges + accuracy + failure modes + mounting
        |                             |
   SIM firmware sample()         gateway decoder (registry.py)
   writes these bytes            parses via the card, never via code
```

Three executable references keep the two ends honest:

- `gateway/scanner/sim_source.py`: the simulator, byte-for-byte reference of every payload.
- `firmware/rehearsal_advertiser/`: a known-good single-sensor radio reference.
- `python -m gateway run`: the integration test; if your build's frames decode and display, the contract holds.

**Rule for all future changes:** a payload change is a *schema version bump* in three places at once (module, card, simulator), never a quiet edit. The `schema_version` byte in every frame exists so old gateways detect newer layouts instead of misdecoding them. This is also the ecosystem play: a third party adds a sensor to the platform by publishing a card plus a module; no gateway code changes.

## 4. Firmware design decisions mapped to agentic principles

| What you will see in the code | Classical instinct | Why it is this way (agentic reason) |
|---|---|---|
| A failed read still advertises, with `sensor_ok` cleared (`main.cpp`, every module) | "Don't send bad data" | An agent cannot interrogate silence. An explicit fault frame is perception; a missing frame is ambiguity. Silent garbage is the one unforgivable output. |
| DS18B20 module reports the raw −127/+85 values while flagging them bad (`ds18b20_mod.cpp`) | "Filter out garbage readings" | The bad value is *teaching data*: the card documents why +85.00 is a reset artifact, and the agent (and student) learn to catch it. Filtering would hide the lesson and the fault. |
| BME688 reports present-but-not-ok with zeroed fields until BSEC2 is integrated (`bme688_mod.cpp`) | "Stub it with plausible values so the demo works" | A fabricated IAQ number is indistinguishable from a real one downstream. An agent would reason on it. The firmware's first rule: never fabricate. This is scaffolding that tells the truth. |
| Sequence counter persisted in NVS, resuming *ahead* after reboot (`seq_store.cpp`) | "Counters can restart at zero" | The gateway computes delivery ratio from seq gaps. A counter restarting at zero looks like 65,000 lost packets; resuming ahead looks like a small gap. The agent's data-quality perception depends on this counter being trustworthy. |
| Monotonic `tick_ms` in every frame | "Arrival time is good enough" | Every multi-sensor inference is a time-alignment problem. BLE scan-window jitter corrupts arrival times; an agent would happily explain the artifact as physics. The gateway reconciles tick against arrival to strip jitter. |
| 4-20 mA module refuses to map out-of-band current, clears `sensor_ok` (`analog420_mod.cpp`) | "Clamp to range and continue" | The live zero is a sixty-year-old machine-readable fault contract. Below 3.8 mA is a *wiring fault*, never a reading. The agent's rule engine and `validate_reading` act on that semantic. |
| Fault injection as a first-class feature with its own status bit (`fault_inject.cpp`) | "Debug code, strip for production" | It is curriculum. The instructor injects a stuck value; the student's agent must catch the lie from data alone; the `fault_injected` bit is the instructor's truth channel. Keep it in production builds. |
| No thresholds, no smoothing, no interpretation in firmware (`main.cpp` design rules) | "Pre-process at the edge" | Interpretation belongs to the layer that has the card, the history, and the context: the gateway and the agent. The SIM that "helpfully" smooths a trace destroys the evidence the agent reasons over. Exception: self-protection only. |
| No deep sleep (`power.cpp` header note) | "Battery devices must sleep" | Kits run on power banks, and power banks cut output below ~50-60 mA average. A deep-sleeping SIM gets its supply killed mid-deployment. Continuous advertising is the keep-alive. Revisit only with guaranteed low-current packs. |
| SEN0193 refuses to output percentages before calibration anchors exist (`sen0193_mod.cpp`) | "Default calibration is fine" | "No Meaning Without Calibration": an uncalibrated percentage is a fabricated number. The agent runs the calibration as a dialogue (`cal12 dry` / `cal12 wet`) and the anchors persist in NVS. Until then, raw millivolts plus not-ok is the honest output. |
| JSN-SR04T does no temperature correction on the SIM (`jsn_mod.cpp`) | "Correct at the source" | Deliberate: the correction needs another sensor's data (DS18B20). Cross-sensor correction is the agent's job ("One Sensor Corrects Another"), assembled from cards at the gateway. The SIM reports what it measured. |
| Water trace excitation duty-cycled to ~0.1% (`water_mod.cpp`) | (good practice anyway) | Also a card-documented failure mode: the gateway watches the dry baseline drift, and the agent learns that sensor longevity is a design property, not luck. |

## 5. The teaching layer you are also building

This kit is for a course, "AIoT and Climate Change", whose stated goal is teaching students to *architect* agentic systems, not to consult a chatbot. The course carries a vocabulary of fourteen named design patterns (one per sensor deck, table in `00_ARCHITECTURE_AND_CODE_STRUCTURE.md` Section 9; capstone briefs in `15_CAPSTONES_WITH_PATTERN_CALLBACKS.md`). Several patterns are implemented *in the code you own*:

- **Design for the Failure Path** (4-20 mA live zero; every status bit).
- **Events, Not Samples** (reed/PIR/AT42 counters that survive packet loss).
- **No Meaning Without Calibration** (SEN0193 anchors).
- **Is Silence Good News?** (seq heartbeat; the gateway watchdog that distinguishes a dry floor from a dead sensor).
- **Architect What the AI Cannot Know** (the SPL envelope detector: only amplitude exists past the hardware; no firmware change can leak speech, and that guarantee is the point).

When you review a change, ask whether it weakens one of these. A change that makes the firmware "smarter" usually makes the agent blinder.

## 6. Practical checklist for the hardware phase

1. **Pins:** `include/pins.h` only. Everything is a macro, per variant, overridable with `-DPIN_X=n`.
2. **First build:** the code has *never been compiled* (no PlatformIO on the authoring machine). Expect first-compile friction, especially ESP32 Arduino core 2.x vs 3.x API drift in BLE and ADC calls. The logic and the contracts are verified; the syntax against your exact toolchain is not.
3. **Bring-up order per variant:** flash → serial console shows `[sim] selftest ...` → `python -m gateway run` on any laptop shows the sensor online with a delivery ratio → inject `fault N stuck` → confirm the gateway's `validate_reading` flags it. That chain proves sensor → SIM → radio → decode → store → tools.
4. **If a SIM build is not received:** flash the rehearsal advertiser on the same board. If the rehearsal is received and the SIM build is not, the fault is in the SIM build; if neither is received, it is the laptop radio or driver.
5. **Open items, in priority order:** verify the Modbus slave address and register map against the real meter (the Rev5 note's "0x340" cannot be an RTU slave address; addresses are 1-247); integrate Bosch BSEC2 for the BME688; calibrate the SPL slope/offset on real hardware; confirm SIM4's connector carries the two GPIO lines the JSN-SR04T needs (it is pulse-width, not analog, whatever the SIM name implies); confirm the 12 V rail for the anemometer and SIM2's 3.3 V budget against the SCD41's ~175 mA emitter pulses.
6. **Never do:** replace a not-ok report with a plausible value to make a demo look good; change a payload without bumping `schema_version` and the card; put a threshold or filter in a sensor module; remove the fault console from production builds.

## 7. Where to read more, in order

1. `00_ARCHITECTURE_AND_CODE_STRUCTURE.md`: the full architecture, payload spec, card schema, capstones, pattern table.
2. `firmware/sim-firmware/README.md`: build, console, payload table, integration chain.
3. `gateway/README.md`: running the gateway, MCP setup, porting notes for Raspberry Pi / Uno Q.
4. `AIoT_Climate_Change_Kit_AI-First_Review.md`: the original review that set this direction; short, and explains the "why" at the product level.
5. `CONVERSATION_LOG_2026-08-05.md`: the full design conversation with the course owner's prompts verbatim; useful when you wonder "was this deliberate?" (it almost always was, and the log says why).
6. Sensor decks (`sensor_decks/`): each opens with the AI-first framing and its named pattern; the technical card slides carry the same numbers as the JSON cards.

One closing orientation. In an assistant-AI world, hardware ships and the AI is bolted on afterwards to explain it. In this project the order is reversed: the machine-readable contract came first, and both the firmware and the gateway are implementations of it. You are not building a sensor board that an AI happens to read. You are building the sense organs of an agent, and the honesty of those organs (status bits, sequence counters, refusal to fabricate) is what makes everything above them trustworthy.
