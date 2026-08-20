# Sensor 11: SCT-013 Split-Core Current Transformer - AC Current / Power (SIM4, Analog)

## Slide 11.1: AI-First: The Old Way and the New Way

**Slide content:**
- Old way: the electricity bill arrives weeks after the waste happened
- New way: an AI watches the power live, minute by minute
- The AC cooling an empty classroom shows up as it happens
- The AC left running all weekend no longer hides in a total
- You set the goal; the AI does the constant accounting

**Narration:**
How do you find out you wasted electricity? The old way, a bill arrives at the end of the month. It is like reading last month's newspaper: everything in it already happened, and you cannot change any of it. The bill also tells you only the total, never the culprit. The new way clips a small sensor around one wire, and an AI watches the power flowing through it live, minute by minute. Now waste has nowhere to hide. The air conditioner cooling an empty classroom at lunchtime shows up at lunchtime. The unit someone forgot on Friday evening is caught on Friday evening, not on the bill three weeks later. The AI can see the pattern, connect it with who is actually in the room, and alert while it still matters. Your role in the new way: you set the goal, cut the waste, keep the comfort, and the AI does the constant accounting that no person would ever keep up.

## Slide 11.2: AI-First: What the AI Must Know About This Sensor

**Slide content:**
- The clamp measures the real current in a wire, without touching metal
- Most sensors help the AI guess; this one proves things
- Its one weakness: a half-closed clamp reads low while looking believable
- So installation ends with a test: a kettle of known power, measured
- The test result is written on the sensor's ID card the AI reads

**Narration:**
This sensor clips around a wire like a clothes peg and measures the current flowing inside, without touching any bare metal. That makes it safe to install, and it makes it special in one more way. Most sensors in the kit help the AI form a guess: motion suggests people, gas suggests a crowd. This one measures hard fact, the actual electricity being used right now. It is the instrument that can prove the AI right or wrong. But the AI must know its one weakness. If the clamp's jaw is not snapped fully shut, it under-reports, and it does so believably: the numbers look fine, just smaller than the truth. No single reading reveals the problem. Think of a bathroom scale on an uneven floor: it shows a plausible weight, and you only catch it by weighing something you already know. So every installation ends the same way: a kettle, with its power printed on the label, is run on the circuit, and the clamp's answer is compared against the truth. That result is written on the sensor's ID card, where the AI can check it. Trust starts with knowing exactly how your instrument could lie.

## Slide 11.3: The Agentic Pattern: The Agent Audits Itself

**Slide content:**
- Pattern in one line: advice must come back with a receipt
- Like a shop showing the discount on the bill, not just the advert
- The AI predicts a saving; the clamp measures what really happened
- If the numbers disagree, the AI investigates and revises its advice
- You design the thinking; the AI does the watching

**Narration:**
The pattern here is the one that separates a true agent from a chatbot: the agent audits itself. In one line, advice must come back with a receipt. Think of a shop sale. The advert promises 30 percent off; the receipt shows what you actually paid; you trust the receipt. Our AI works the same way. It studies when rooms are really occupied and proposes a smarter cooling schedule, predicting a saving. Then the clamp does the accounting: two weeks measured the old way, two weeks the new way, and the two totals meet on paper. If the saving is real, the AI has proof anyone can inspect. If it is not, the interesting work begins: was the room busier than expected, was a window left open? The AI investigates, revises its advice, and predicts again. An assistant stops at the recommendation; an agent follows through to the receipt. You decide what must be proven. The AI runs the proof, honestly and endlessly. Now let us see how a clamp measures electricity without touching a single wire.

## Slide 11.4: What It Is

**Slide content:**
- A clamp that measures electric current through a wire without touching any conductor
- Principle: alternating current creates an alternating magnetic field; a ferrite ring around the wire harvests it
- Split-core: the ring hinges open, clips around one insulated wire, snaps shut; 60-second install
- Secondary winding scales thousands of milliamps down to a small measurable signal
- SCT-013-030 variant: 30 A primary becomes 1 V output, burden resistor built in
- Non-invasive and safe: no circuit is broken, no live part is exposed

**Narration:**
How do you measure the electricity an air conditioner uses without an electrician, without cutting a wire, and without going anywhere near a live terminal? With physics that Faraday gave us two centuries ago. Any wire carrying alternating current is wrapped in an invisible, alternating magnetic field. The SCT-013 is a ferrite ring, split in half and hinged like a clothes peg, that clips around a single insulated wire. The ring gathers that magnetic field, and a coil of many turns wound on the ring converts it back into a small, faithful copy of the current flowing in the wire. Thirty amps in the conductor becomes one volt at the sensor's plug, a scale factor of 33.3 millivolts per amp in the variant we use. Installation takes under a minute: open the jaw, clip it around one wire, snap it shut. Nothing is cut, nothing is unscrewed, and the wire's insulation is never breached, which is why this style of sensor is called non-invasive and why it is the standard tool of every energy auditor. One safety rule is built into our chosen variant: the SCT-013-030 contains an internal burden resistor that keeps its output terminated at all times. Always use burden-resistor variants; a current transformer with an open secondary can develop hazardous voltages. Ours cannot.

## Slide 11.5: What It Does in Practice

**Slide content:**
- Energy audits: appliance-level and circuit-level kWh, the auditor's first instrument
- Machine state: compressor draws 8-20 A running, under 0.5 A idle; on/off is unambiguous
- Predictive maintenance: rising current at constant load flags bearing wear; short-cycling flags refrigerant loss
- Safety: sustained current near breaker rating warns of overload before trip or fire
- Occupancy proxy: a computer lab full of powered PCs betrays itself electrically
- Grid and renewables: solar generation logging (AC side), EV charge sessions, phase balance

**Narration:**
What does the world do with a clamp meter that logs continuously? First, it audits. Energy consultants clamp circuits one by one to discover where a building's kilowatt-hours actually go, and the answers routinely embarrass assumptions: the forgotten pump, the AC serving an empty wing, the 10 to 15 percent of campus load that is equipment idling on standby overnight. Second, it reports machine truth. An HVAC compressor draws eight to twenty amps running and almost nothing idle, so the current trace is an unambiguous on/off log that no thermostat display can contradict; a compressor that starts more than six or eight times an hour is short-cycling, usually refrigerant loss, and the trace counts every cycle. Third, it predicts failures: a motor whose current creeps upward week over week at the same load is telling you its bearings are wearing, an electrical symptom that appears before the thermal one. Fourth, it protects: a circuit running sustained above eighty percent of its breaker rating is a fire statistics category, and chronic overload is invisible until it is logged. Fifth, unexpectedly, it counts people: a computer lab with thirty machines awake is electrically loud even when the students are motionless, exactly where motion sensing fails. And on the generation side it verifies solar output and logs EV charging sessions, closing loops on the clean side of the meter.

## Slide 11.6: Technical Card

**Slide content:**
- Measurand: AC RMS current; apparent power S = V × I at a nominal 230 V; energy by integration
- Variant: SCT-013-030, 0-30 A, output 0-1 V, 33.3 mV/A, internal burden resistor
- Firmware: approximately 1 kHz burst sampling, RMS computed on the SIM, one reading per second
- Floor: approximately 24 mA unassisted (approximately 3 mA with oversampling); below approximately 50 mA unreliable
- For small loads use SCT-013-005 (5 A, 200 mV/A); ESP32 ADC nonlinearity limits the bottom decade
- Packaged sensor dimensions: [PLACEHOLDER]
- Interface and connector details: [PLACEHOLDER: keyed harness part number]
- SIM assignment: SIM4 (Analog), signal biased to mid-rail before the ADC

**Narration:**
Here is the honest specification. Our standard variant, the SCT-013-030, spans zero to thirty amps and outputs zero to one volt, 33.3 millivolts per amp, with the safety burden resistor inside. SIM4 biases this AC signal to mid-rail, samples it in bursts at roughly one kilohertz, computes the root-mean-square value in firmware, and broadcasts one current reading per second. Multiply by a nominal 230 volts and you have apparent power; integrate over time and you have energy. For compressors and motors, whose power factor is near unity, apparent power tracks real power within five to ten percent, which is ample for an audit. Now the limits, because every sensor has them. The 12-bit ADC step corresponds to about 24 milliamps of primary current, and oversampling pushes the effective floor to a few milliamps, but the ESP32's ADC is at its worst near the bias point, so treat anything below approximately 50 milliamps as unreliable: a projector in standby at 22 milliamps is genuinely invisible to this variant. When the assignment is small loads, phantom power, a lighting branch, swap in the SCT-013-005, which trades a 5 amp ceiling for six times the sensitivity. Choosing the variant to match the circuit is itself a lesson in dynamic range. Packaged dimensions and the keyed harness details are placeholders pending the production sensor.

## Slide 11.7: Climate Change Applications

**Slide content:**
- Measured, not modelled: baseline fortnight vs intervention fortnight gives kWh savings as fact
- Carbon arithmetic: kWh × grid factor (India approximately 0.82 kg CO2/kWh) = measured emissions avoided
- Finds the waste: AC in empty rooms, weekend loads, phantom standby, simultaneous heat-and-cool
- Verifies the clean side: solar output vs irradiance expectation catches degradation and soiling
- Institutional force: finance committees act on measured numbers; models get filed

**Narration:**
Every climate project in this course produces a model; this sensor produces evidence, and the difference decides whether anything changes. The canonical experiment runs in two phases. For a baseline fortnight, the building runs as it always has while the clamp logs every watt-hour the HVAC circuit consumes. Then the sensor-driven controls switch on, and the clamp logs another fortnight. Subtract. The result is not "we estimate thirty percent savings from our occupancy model"; it is "847 kilowatt-hours became 591, a measured 30 percent reduction", and each kilowatt-hour converts to carbon at the Indian grid's emission factor of approximately 0.82 kilograms of CO2 per kilowatt-hour. Two hundred and fifty-six saved kilowatt-hours is roughly 210 kilograms of CO2, per room, per fortnight, measured. Why does this matter so much? Because institutions act on measured numbers. A facilities committee shown a model files it; shown a metered before-and-after with a payback period, it procures. Along the way the clamp finds the waste that models miss: the air conditioner serving an empty room at 8 a.m., the loads that never sleep on weekends, the phantom standby consumption, and, paired with a window sensor, the heat-and-cool absurdity of conditioning the outdoors. On the clean side, it verifies that the rooftop solar array actually delivers what the irradiance says it should, catching soiling and degradation. Mitigation begins with measurement, and this is the measuring instrument.

## Slide 11.8: Fusion Partners

**Slide content:**
- SCD41 + PIR: occupancy × HVAC current, the five-row waste table (AC on, room empty, at 08:00 and 18:00)
- VEML7700: lighting current during daylight-sufficient hours = quantified lighting waste
- RS485 energy meter (SIM5): class-1 reference to cross-check the clamp; catches the partially closed jaw
- SPL: acoustic hum and electrical draw must agree on machine state; disagreement = fault
- Jaw-closure check: kettle reference load at install, reading must match P/230 V within ±10%

**Narration:**
The clamp's data becomes decisive when an agent lays it beside occupancy. Cross-reference HVAC current with CO2 and motion and every hour of the day lands in one of five rows: AC on with the room full is correct; AC on at 8 a.m. with CO2 at 420 ppm is waste; AC on at lunch with the room empty is waste; AC off at 3 p.m. with the room full is a comfort failure; AC on at 6 p.m. with the building locked is the most expensive row of all. The agent builds this table automatically from `query_timeseries`, aligned on the tick, and the table is the energy audit. With the VEML7700 the same join works for lighting: fixture current flowing during hours when daylight already exceeds the target is pure quantified waste. Two partnerships are about trust rather than discovery. The RS485 energy meter on SIM5 is a class-1 instrument, so clamping the same load both ways cross-checks the clamp, and this matters because of the CT's signature failure: a jaw that has not snapped fully shut, held ajar by a thick cable jacket or a tired spring, under-reads systematically with no error flag, sometimes by half. The acceptance ritual at every installation: run a kettle of known rated power on the circuit and confirm the clamp reads its wattage over 230 volts within ten percent. And the SPL sensor supplies an independent second opinion, because a compressor that hums without drawing current, or draws without humming, is a fault either way.

## Slide 11.9: Capstone C8: What Does the Machine's Electrical Signature Say Before It Fails?

**Slide content:**
- Question: can we hear a machine failing in its current draw weeks before it stops?
- Sensors: SCT-013 (electrical signature), SPL (acoustic baseline), DS18B20 (thermal lag confirmation), RS485 meter (reference)
- Contradiction to resolve: baseline drift can be seasonal load change, sensor drift, or genuine wear; which is it?
- Decision: a maintenance recommendation with evidence, or a defended verdict that the machine is healthy
- Agents: nightly watchdog fits trends, tests the three hypotheses, and adjudicates with the reference meter

**Narration:**
The capstone question is predictive maintenance stated plainly: can students detect a machine failing before it fails? The subject is a real campus workhorse, a water pump or an AC compressor. The SCT-013 logs its current signature continuously: running amplitude, the starting surge, cycle frequency. The SPL sensor logs its acoustic baseline beside it, the DS18B20 tracks its housing temperature, and the class-1 RS485 meter sits on the same circuit as the referee. Failure physics stack up in a known order: friction rises first, so current at constant load creeps upward and starting surges stretch longer; noise rises next; heat arrives last. The contradiction at the heart of the project is that a rising current baseline has three rival explanations: genuine mechanical wear, a seasonal change in load (a pump lifting from a lower water table works harder with healthy bearings), or instrument drift, including the clamp's own jaw slowly working open. A nightly agent runs the discrimination through the MCP tools: it fits the week's trend, cross-checks the clamp against the reference meter to rule out instrument drift, tests the seasonal hypothesis against tank levels and weather, and checks whether the acoustic baseline moved in sympathy. When only the wear hypothesis survives, it drafts a maintenance recommendation with its evidence chain. The students' deliverable is the adjudicated verdict, repair now, monitor, or healthy, defended against all three hypotheses, with the cost of being wrong in each direction stated.
