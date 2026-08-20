# Capstone Projects, Pattern Edition

**Companion to:** `00_ARCHITECTURE_AND_CODE_STRUCTURE.md` (Section 8 catalog, Section 9 pattern vocabulary)
**Purpose:** the capstone briefs below call back the fourteen agentic design patterns by name. Students met each pattern once, inside one sensor deck. The capstones are where the vocabulary stops being deck-local: every brief names the patterns it exercises, and the assessment grades whether the student can recognise and apply a pattern outside the deck that taught it.

How to read a brief: each capstone is a question with a decision at the end. The sensors are the witnesses, the patterns are the reasoning moves, and the agent (through the gateway MCP tools) is the actor that makes the moves. The student architects; the agent executes; the physical world grades both.

---

## Pattern Coverage Matrix

| Pattern (taught in deck) | C1 | C2 | C3 | C4 | C5 | C6 | C7 | C8 |
|---|---|---|---|---|---|---|---|---|
| Predict, Then Measure (01) | X |  | X |  |  |  | X |  |
| Adjudicating Two Witnesses (02) |  |  | X |  |  |  | X |  |
| Absence of Evidence (03) | X | X |  |  | X |  |  |  |
| Design for the Failure Path (04) |  |  |  |  |  | X |  | X |
| Contracts All the Way Down (05) |  |  |  |  |  |  |  | X |
| Evidence With Latency (06) | X |  | X |  |  |  |  | X |
| The Agent Writes the Rule (07) |  | X |  |  |  |  | X |  |
| Architect What the AI Cannot Know (08) |  |  | X | X |  |  |  |  |
| One Sensor Corrects Another (09) |  |  |  | X |  | X |  |  |
| Events, Not Samples (10) | X |  |  | X | X |  |  |  |
| The Agent Audits Itself (11) | X | X |  |  |  |  |  | X |
| No Meaning Without Calibration (12) |  |  |  |  |  | X | X |  |
| Is Silence Good News? (13) |  |  |  |  | X | X |  |  |
| Context Gates Meaning (14) | X |  |  | X |  |  |  |  |

Every pattern is called back at least twice. No capstone exercises fewer than three patterns.

---

## C1: Is This Room Healthy, and Is the HVAC Earning Its Energy Bill?

**Sensors:** SCD41 (SIM2), PIR (SIM3), DS18B20 (SIM1), SCT-013 (SIM4), reed switch (SIM3)
**The contradiction to resolve:** the occupancy evidence disagrees with itself. PIR goes silent while CO2 keeps rising; temperature drops while the window is open; the AC runs while the room is empty. The agent must build one coherent occupancy-and-energy story from witnesses that individually mislead.
**The decision at the end:** a revised HVAC schedule, deployed as an edge rule, with a measured kWh saving attached.

**Patterns in play, by name:**

- **Absence of Evidence (03):** PIR silence during a lecture is the founding problem of this capstone. The agent maintains a decaying occupancy belief and refuses to conclude "empty" from PIR alone.
- **Evidence With Latency (06):** CO2 confirms or vetoes the fast channels 2-5 minutes late. The agent's state machine must exploit the lag, not be confused by it: fast channels propose, the slow integrator ratifies.
- **Events, Not Samples (10):** the reed switch's door and window events are the context that disambiguates. A CO2 drop after `window_open` is ventilation, not departure. The agent treats the event log as the spine of the narrative.
- **Context Gates Meaning (14):** taught on the AT42QT1010, applied here to the reed switch: while the envelope is open, the agent marks CO2 and temperature readings invalid for control decisions. Same move, different bit.
- **Predict, Then Measure (01):** before deploying the new schedule, the student and the agent each commit a numeric prediction of weekly kWh saving. The clamp meter then grades both.
- **The Agent Audits Itself (11):** baseline fortnight versus intervention fortnight on the SCT-013. The recommendation is not done until the measured saving exists.

**Orchestration sketch:** a question agent runs `capture_experiment` across all five sensors for the baseline; the cloud loop reasons over the aligned series (`query_timeseries`, reconciled on `tick_ms`); the resulting rule goes through `deploy_rule` behind human approval; a watchdog agent then audits weekly and annotates deviations.

**Pattern-aware assessment:** name the pattern you used when PIR and CO2 disagreed, and show the trace. Show the prediction you committed before the measurement and defend the gap. Identify one moment where the agent would have been wrong without the reed switch event log, and name the two patterns that saved it.

---

## C2: Should the Lights Be On at All?

**Sensors:** VEML7700 (SIM2), PIR (SIM3), SCT-013 (SIM4)
**The contradiction to resolve:** motion says yes, daylight says no. A PIR-only controller lights a corridor that is already at 600 lux from the sun.
**The decision at the end:** a deployed lighting rule (`motion AND lux < threshold`), plus a measured statement of how many lighting kWh the daylight term saved.

**Patterns in play, by name:**

- **The Agent Writes the Rule (07):** the control law is one line. The student states intent in natural language; the agent authors the deterministic rule and its thresholds from the IS 3646 targets; the rule runs in the edge loop with no model in the path.
- **Absence of Evidence (03):** the lights-off condition depends on "no motion for T seconds". The student must set T with the PIR blind spot in mind, and justify what silence is allowed to mean in a corridor versus a store room.
- **The Agent Audits Itself (11):** the SCT-013 on the lighting circuit measures what the rule actually saved. The agent compares fixed-schedule baseline against rule-driven operation and reports measured, not modelled, savings.

**Orchestration sketch:** design-time session produces the rule via `deploy_rule`; the runtime side is deliberately model-free; a monthly cloud-loop audit queries the lighting circuit series and the lux series, and proposes threshold adjustments as a new rule version, never a live intervention.

**Pattern-aware assessment:** explain why this capstone puts the model at design time only, and name the pattern. Show one week of lux data and mark the hours your rule kept lights off that a PIR-only rule would have lit.

---

## C3: Is This Space Comfortable by the Numbers?

**Sensors:** BME688 (SIM2), SCD41 (SIM2), DS18B20 (SIM1), SPL (SIM4)
**The contradiction to resolve:** the BME688's IAQ index says the air is poor while the SCD41 says CO2 is modest, or the reverse. Two instruments testify about the same room and disagree.
**The decision at the end:** a comfort verdict against ASHRAE 55 / ISO 7730 bands, with an explicit adjudication of the conflicting witnesses and a recommended intervention.

**Patterns in play, by name:**

- **Adjudicating Two Witnesses (02):** the core of the capstone. BME688 eCO2 is an inference from VOC chemistry; SCD41 is a direct photoacoustic measurement. The agent treats the first as testimony, the second as reference, and explains disagreements (a VOC event is real information, not an error).
- **Evidence With Latency (06):** comfort complaints arrive instantly; CO2 accumulates slowly. The agent aligns the SPL activity trace with the CO2 rise to separate "room just filled" from "ventilation failing".
- **Architect What the AI Cannot Know (08):** the SPL channel contributes activity level while structurally unable to contribute speech content. The student documents this hardware privacy boundary in the deployment journal as part of the ethics section.
- **Predict, Then Measure (01):** the student predicts the lunchtime CO2 peak from the room volume and timetable before capturing it. The mass-balance model meets reality.

**Orchestration sketch:** `capture_experiment` over a full teaching day; the cloud loop runs the adjudication recipe; `annotate` records events the sensors cannot see (projector on, windows opened); the verdict cites the aligned traces.

**Pattern-aware assessment:** produce one adjudication where you overruled the BME688 and one where you believed it over the naive reading, naming the pattern both times. Defend the SPL privacy claim to a sceptical parent using the hardware argument, not a policy promise.

---

## C4: Is the Canteen Safe, and How Long Is the Queue?

**Sensors:** DS18B20 waterproof (SIM1), reed switch (SIM3), JSN-SR04T (SIM4), SPL (SIM4), AT42QT1010 (SIM3)
**The contradiction to resolve:** the heat lamp thermometer alarms on an empty lamp; the queue estimate jumps when a trolley parks in the beam. Raw readings are honest; their meaning depends on context the readings do not carry.
**The decision at the end:** a HACCP-compliant temperature log that only records when food is present, and a queue-depth feed the canteen staff actually trust.

**Patterns in play, by name:**

- **Context Gates Meaning (14):** the AT42QT1010 tray-presence bit gates the DS18B20 log. No tray, no HACCP record, no false alarm. The cheapest fusion in the course, and the reason the food-safety log is credible.
- **Events, Not Samples (10):** cold-store reed events disambiguate every temperature excursion: door-open plus rising temperature is carelessness, door-closed plus rising temperature is a compressor emergency. Two different alerts, two different actions.
- **One Sensor Corrects Another (09):** the JSN-SR04T queue distance drifts with kitchen heat; the agent applies the DS18B20-derived speed-of-sound correction before converting distance to queue length.
- **Architect What the AI Cannot Know (08):** the SPL sensor estimates rush intensity without recording a single word spoken in the queue. The deployment journal documents the envelope-detector boundary.

**Orchestration sketch:** the edge loop carries the two safety rules (cold-chain alert, heat-lamp alert, both gated); the cloud loop correlates queue depth, noise, and serving events for the weekly operations report; every alert cites its disambiguating event.

**Pattern-aware assessment:** show one excursion your gating suppressed and one it correctly passed, naming the pattern. Reconstruct a compressor failure from the event log alone. Quantify the queue-length error you removed with the temperature correction, and name that pattern.

---

## C5: Is the Restricted Zone Secure Against More Than One Threat?

**Sensors:** reed switch (SIM3), PIR x2 (SIM3), VEML7700 (SIM2), SCT-013 (SIM4), water level trace (SIM4)
**The contradiction to resolve:** a monitoring system that is quiet for months must prove it is quiet because nothing is wrong, not because it is dead. And when something does happen, one signal is never enough to act on.
**The decision at the end:** a multi-hazard monitor (intrusion, tamper, flood, equipment) with a defined confirmation chain per threat and a liveness guarantee.

**Patterns in play, by name:**

- **Events, Not Samples (10):** the intrusion chain is a timestamp-ordered narrative: `door_open` then `PIR_zone1` then `PIR_zone2`. An open door with no PIR follow-up is a different threat (door ajar) with a different response.
- **Absence of Evidence (03):** no PIR activity in a zone the door log says was entered is itself an alarm. The agent reasons about missing corroboration, not just present signals.
- **Is Silence Good News? (13):** the water level trace and the reed switch may not fire for a semester. The watchdog agent checks sequence-counter heartbeats and status bits on schedule, so silence is verified alive, never assumed.
- **Design for the Failure Path (04):** taught on the 4-20 mA live-zero, applied here: every channel in the monitor must have a state that distinguishes "measuring zero" from "broken". The student specifies that state per sensor before deployment.

**Orchestration sketch:** all confirmation chains run as edge rules; the cloud loop's watchdog agent audits liveness daily and files annotations; any alert opens an agent-led investigation that pulls the aligned series from every witness and writes the incident narrative.

**Pattern-aware assessment:** submit the fault-injection exercise: the instructor kills one sensor silently, and your system must report the death before the instructor triggers the hazard. Name the pattern that caught it. Write the incident narrative for a staged intrusion using only the event log.

---

## C6: Where Does the Campus Water Actually Go?

**Sensors:** JSN-SR04T (SIM4), water level trace (SIM4), SEN0193 (SIM4), 4-20 mA level/flow transmitter (SIM4), SCT-013 on the pump (SIM4)
**The contradiction to resolve:** the tank level says water left, the irrigation soil says it never arrived, and the pump current says the pump ran. Somewhere between the sensors is a leak, a theft, or a calibration error, and the agent must say which.
**The decision at the end:** a water balance for one building or garden zone, with losses located and quantified, and a pump-control rule deployed.

**Patterns in play, by name:**

- **One Sensor Corrects Another (09):** tank level from the JSN-SR04T is temperature-corrected before any volume is computed; an afternoon sun on the tank lid otherwise fabricates a phantom drawdown.
- **No Meaning Without Calibration (12):** the SEN0193 percentages are meaningless until anchored, and the 4-20 mA transmitter's card scaling must match its nameplate. The agent runs the calibration dialogues and records the anchors before the balance is attempted.
- **Design for the Failure Path (04):** the 4-20 mA transmitter's live-zero separates "empty pipe" from "cut cable". The balance calculation refuses to ingest out-of-band samples as zeros.
- **Is Silence Good News? (13):** the overflow trace at the tank rim should never fire. The watchdog verifies it is alive each week, because an overflow event missed by a dead sensor is the costliest silent failure in the system.

**Orchestration sketch:** a fortnight of `capture_experiment` across the water chain; the cloud loop computes the balance and flags the residual; pump thresholds (20% on, 90% off) deploy as edge rules; the agent's report states volumes with the calibration provenance attached.

**Pattern-aware assessment:** show the water balance with and without the temperature correction and name the pattern that closed the gap. Produce the calibration record the agent wrote, and explain what the balance would have concluded without it.

---

## C7: When Should We Water, and Did It Work?

**Sensors:** SEN0193 (SIM4), VEML7700 (SIM2), DS18B20 (SIM1), BME688 (SIM2)
**The contradiction to resolve:** the soil says dry, the sky says rain is coming, and yesterday's irrigation says the probe should read wet. The agent must decide when watering is needed and then prove the schedule it chose actually saved water.
**The decision at the end:** an irrigation schedule deployed as an edge rule, and a measured litres-per-week comparison against the timer-based baseline.

**Patterns in play, by name:**

- **No Meaning Without Calibration (12):** the capstone opens with the agent-guided calibration dialogue: probe in air, probe in water, anchors written to NVS and mirrored to the card. Every later decision inherits its credibility from this hour.
- **The Agent Writes the Rule (07):** the watering decision (moisture below threshold AND no heavy rain signal AND early morning) is authored by the agent at design time and runs deterministically; irrigation cannot depend on cloud connectivity.
- **Adjudicating Two Witnesses (02):** the BME688 humidity trace and the SEN0193 soil trace both speak about wetness and routinely disagree (humid air over dry roots). The agent adjudicates with the VEML7700 light-dose series as context for evapotranspiration.
- **Predict, Then Measure (01):** before each irrigation cycle, the agent predicts the post-watering moisture plateau; a plateau that misses the prediction flags channelling, runoff, or a drifting probe.

**Orchestration sketch:** calibration dialogue first; rule deployment behind approval; a daily cloud-loop review correlates moisture decline with light dose and temperature; the semester report compares measured consumption against the timer baseline.

**Pattern-aware assessment:** show one day where air humidity and soil moisture disagreed and name the pattern you applied. Present the prediction-versus-plateau record and diagnose the one cycle that missed. State the measured water saving and its calibration provenance.

---

## C8: What Does the Machine's Electrical Signature Say Before It Fails?

**Sensors:** SCT-013 (SIM4), SPL (SIM4), DS18B20 (SIM1), RS485 energy meter (SIM5)
**The contradiction to resolve:** the meter says the motor is fine, the clamp says current is creeping up, the microphone hears a new whine, and the thermometer sees nothing yet. Which witness leads, which lags, and when do you call maintenance?
**The decision at the end:** a maintenance recommendation with a lead-time estimate, backed by a cross-checked multi-channel baseline.

**Patterns in play, by name:**

- **Contracts All the Way Down (05):** the RS485 meter is read strictly from its register-map contract served as an MCP resource; the agent writes the decoder from the map and never guesses a register or a scale factor.
- **The Agent Audits Itself (11):** the SCT-013 and the class-1 meter measure the same circuit. The agent cross-checks them at installation (reference load acceptance test) and continuously; divergence indicts the clamp's jaw, not the motor.
- **Evidence With Latency (06):** the failure signals arrive in order: current rises first, acoustics second, temperature last. The agent's model ranks the channels by lead time and treats agreement across two leading channels as the maintenance trigger.
- **Design for the Failure Path (04):** a Modbus timeout or a stuck register is a communications fault, not a healthy motor; the status bits keep dead channels out of the baseline.

**Orchestration sketch:** a multi-week baseline via `capture_experiment`; a watchdog agent tracks baseline drift per channel and annotates excursions; the maintenance recommendation is generated in the cloud loop with the full evidence chain and the cross-check record attached.

**Pattern-aware assessment:** demonstrate the acceptance test and name the pattern it serves. Given the instructor's doctored dataset (one channel drifting for a false reason), identify the channel, the fault, and the pattern that exposed it. Defend your maintenance lead-time estimate.

---

## Instructor Note: Grading the Vocabulary

Across the eight capstones, require each student team to log, in the deployment journal, every moment they consciously applied a named pattern. The final viva asks for three things: one pattern applied in a capstone far from the deck that taught it, one moment a pattern prevented a wrong conclusion (with the trace), and one situation where none of the fourteen patterns fit and something new was needed. The third question is where the next revision of this course comes from.
