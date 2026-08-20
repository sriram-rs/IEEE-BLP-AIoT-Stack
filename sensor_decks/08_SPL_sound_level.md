# Sensor 08: SPL Sensor (MEMS Microphone + Envelope Detector) - Sound Pressure Level (SIM4, Analog)

## Slide 08.1: AI-First: The Old Way and the New Way

**Slide content:**
- Old way: a person walks in, listens, judges, walks away
- New way: an AI watches the loudness every second, and acts
- The AI never gets bored, never goes home, never stops noticing
- The library turns noisy; the AI notices immediately, not at closing time
- Your new role: decide what the AI watches for, and what it does

**Narration:**
How do you know if the library is too loud? The old way: someone walks in, listens for a moment, makes a judgement, and walks away. Five minutes later the room changes and nobody knows. The new way turns this around. A small sensor measures the loudness of the room, and an AI watches that number every second of every day. It is like having a librarian who never goes home and never gets distracted. When the noise crosses the limit at four in the afternoon, the AI notices at four in the afternoon, not when someone complains at closing time. And it can act: log the event, light a quiet-please sign, or send a message. Notice what your role becomes in this new way. You are no longer the person reading the meter. You are the person who decides what the AI should watch for, and what it should do when it sees it.

## Slide 08.2: AI-First: What the AI Must Know About This Sensor

**Slide content:**
- The AI reads the sensor's ID card: what I measure, how well, how often
- The card says: loudness from 30 to 120 decibels, once a second
- And what it cannot do: it hears how loud, never the words
- The words are erased inside the circuit, by hardware, not by promise
- An AI is only as good as what it knows about its senses

**Narration:**
Before the AI can be trusted with this sensor, it must know two things: what the sensor can say, and what it cannot. Both are written on the sensor's ID card, a small file the AI reads before it reads any data. For this sensor the card says: I report loudness, from a whisper at 30 decibels to a siren at 120, once every second. It also carries a warning: a reading stuck at the very bottom could mean a silent room, or a broken microphone, so check before you conclude. And it states the most important limit of all: this sensor hears how loud, never the words. The speech is erased inside the circuit before any computer sees it. It is like a thick wall: you can tell there is a party next door without catching a single sentence. Here is the sentence to remember from this slide: an AI is only as good as what it knows about its own senses.

## Slide 08.3: The Agentic Pattern: Architect What the AI Cannot Know

**Slide content:**
- Pattern in one line: privacy is built into the hardware, not promised in software
- Like frosted glass: you can see someone is there, never who
- Here, the circuit keeps the loudness and throws the words away
- A promise can be broken; a physical limit cannot
- You design what the AI may know; the AI does the watching

**Narration:**
Here is the first pattern for your collection: architect what the AI cannot know. In one line: if something must stay private, build the privacy into the hardware, do not just promise it in software. Think of frosted glass. Through frosted glass you can see that someone is in the room, but never who it is. That is not a rule someone follows; it is what the glass is. This sensor is frosted glass for sound. The circuit measures how loud the room is and throws the actual sound away, instantly, before anything is stored. So the AI can tell you the canteen has hit its noisy peak, or that the library crossed its quiet limit, but it could not repeat one word of a conversation even if asked. A promise can be broken or hacked; a physical limit cannot. And notice the division of work: you design what the system may know and how it should think, the AI does the constant watching. Keep the frosted glass in mind as we now look at the microphone itself.

## Slide 08.4: What It Is

**Slide content:**
- A MEMS microphone paired with an envelope detector circuit
- Measures loudness, not sound content: output is one DC voltage proportional to RMS sound pressure level
- Reported in decibels (dB), a logarithmic scale matched to human hearing
- No audio is recorded, stored, or transmitted: speech is physically unrecoverable from the signal
- Privacy-preserving by construction, deployable where recording consent is legally complex
- The kit's only sensor for what people and machines are doing, rather than where they are

**Narration:**
What does a room sound like when it is empty? What about when thirty students are writing an exam in silence, or arguing through a group project? This sensor answers those questions with a single number. Inside the package is a MEMS microphone, a tiny mechanical membrane etched into silicon that vibrates with the air pressure fluctuations we call sound. But here is the important design decision: the microphone's output never leaves the package as audio. An envelope detector circuit continuously computes the average loudness of the signal and outputs one slowly varying DC voltage proportional to the sound pressure level in decibels. Think of it as a loudness meter, not a recorder. Nobody can reconstruct a conversation from this signal, because the information simply is not there; only the amplitude survives. That makes the sensor deployable in classrooms, libraries, and offices where audio recording would raise legitimate legal and ethical objections. The decibel scale itself is logarithmic: every 10 dB step means roughly ten times the acoustic power, which matches how our ears perceive loudness. A quiet room sits near 35 dB, conversation near 60 dB, and an alarm above 85 dB. One voltage, read once per second, tells you which of those worlds you are in.

## Slide 08.5: What It Does in Practice

**Slide content:**
- Occupancy and activity: distinguishes an empty room from a silent occupied one, instantly
- Noise compliance: library quiet zones, classroom background limits (IS 3483: 35 dB(A)), office noise mapping
- Equipment health: fan and compressor hum confirms running state; rising baseline flags bearing wear
- Safety events: glass break, impact, alarm confirmation, all from amplitude signatures alone
- Interaction: clap and knock patterns as a control gesture, implemented entirely in firmware
- Urban environment: traffic noise exposure logging at building facades

**Narration:**
Where does a loudness meter earn its keep? Start with people. Sound is the only signal in this kit that responds to activity level: a lecture, a discussion, and an exam all involve the same number of people but sound completely different. Facilities teams use exactly this to enforce library quiet zones and to audit whether classroom background noise stays below the 35 dB(A) limit that Indian standard IS 3483 sets for teaching spaces, because sustained noise above that level measurably impairs learning. Now consider machines. A healthy fan produces a steady hum; a failing bearing produces a slowly rising noise floor weeks before it overheats. A cavitating pump crackles. A compressor that starts and stops too often betrays a refrigerant leak. All of these are amplitude patterns, readable without any audio content. Safety applications follow the same logic: breaking glass produces a sharp impulse above 75 dB with a rise time under a tenth of a second, and a fire alarm produces a sustained level above 85 dB, so the sensor independently timestamps both. And because the SIM firmware can recognise a pattern of two claps or three knocks, the sensor even becomes a simple control interface. One analog voltage, many jobs.

## Slide 08.6: Technical Card

**Slide content:**
- Measurand: sound pressure level, RMS, A-weighted approximation
- Range: approximately 30-120 dB SPL; update rate 1 Hz (sufficient for occupancy and compliance)
- Accuracy: approximately ±2-3 dB after single-point calibration [to be characterised on final hardware]
- Raw device: MEMS microphone (approximately 3-4 mm package) + op-amp envelope detector
- Output: analog DC, 0-3.3 V, proportional to dB level; read by SIM4's 12-bit ADC with oversampling
- Packaged sensor dimensions: [PLACEHOLDER]
- Interface and connector details: [PLACEHOLDER: keyed harness part number]
- SIM assignment: SIM4 (Analog), sensor rail powered from the SIM

**Narration:**
Here is the sensor as an engineering object. The measurand is root-mean-square sound pressure level, expressed in decibels over a working range of approximately 30 to 120 dB, which spans everything from a near-silent room to a machine shop. The raw MEMS microphone is a few millimetres across; the packaged sensor adds the envelope detector stage that converts the raw audio waveform into a smooth DC voltage between 0 and 3.3 volts. SIM4 reads that voltage with the ESP32's 12-bit analog-to-digital converter, applies oversampling to steady the reading, converts it to a dB figure, and broadcasts it once per second inside the BLE advertisement frame, complete with the sequence counter and monotonic tick that every SIM frame carries. One update per second sounds slow for a sound sensor, but remember what we are measuring: occupancy states and machine baselines change over seconds and minutes, not milliseconds. Accuracy after a single-point calibration against a phone sound meter app is approximately plus or minus 2 to 3 dB, which is entirely adequate for threshold and trend work, though not for legal metrology. The final packaged dimensions and the keyed connector details are placeholders on this slide and will be supplied with the production hardware. The sensor card the gateway serves to the AI carries all of these numbers in machine-readable form.

## Slide 08.7: Climate Change Applications

**Slide content:**
- HVAC state confirmation: compressor and fan hum verifies equipment is actually running, or wastefully left on
- Predictive maintenance: rising acoustic baseline catches bearing wear early, extending equipment life and deferring embodied-carbon replacement
- Enables fast HVAC setback: silence plus no motion means the room emptied, cut cooling within about 30 seconds instead of waiting 10-15 minutes for CO2 decay
- Urban adaptation: traffic noise mapping identifies facades needing acoustic (and thermal) glazing upgrades
- Noise is itself an environmental stressor tracked alongside heat and air quality in dense cities

**Narration:**
How does a loudness sensor fight climate change? Three ways. First, energy. Cooling an empty room is the most common energy waste on any campus, and the slowest part of fixing it is knowing the room actually emptied. Carbon dioxide takes five to fifteen minutes to decay after people leave; motion sensors cannot tell a room that emptied from a room full of still people. But when the sound level drops to the bare HVAC hum and stays there while motion is absent, the room is empty now, and the control loop can set back the air conditioning within about thirty seconds. The CO2 sensor then confirms the decision a few minutes later. Second, equipment. A failing bearing announces itself acoustically weeks before it announces itself thermally. Catching it early means a small repair instead of a scrapped motor, and every avoided replacement avoids the embodied carbon of manufacturing new equipment. The sensor also confirms, independently of any thermostat, whether a compressor is running at all, so "the AC was left on all weekend" becomes a logged fact rather than a suspicion. Third, adaptation. As cities densify and warm, noise joins heat as a chronic environmental stressor. Mapping which building facades bear the worst traffic noise tells you exactly where acoustic glazing, which is usually also better thermal glazing, pays off first.

## Slide 08.8: Fusion Partners

**Slide content:**
- PIR (SIM3): motion says where, sound says what; both respond instantly
- SCD41 (SIM2): latency complementarity, SPL instant vs CO2 lagging 2-15 min; SPL proposes, CO2 confirms
- SCT-013 (SIM4): acoustic hum vs electrical current, two independent votes on machine state
- Five-state fusion machine: EMPTY, LOW_OCCUPANCY, OCCUPIED, ACTIVE, ANOMALY
- Agent role: `query_timeseries` across all three, aligned on tick, classifies state and explains its evidence

**Narration:**
No single occupancy sensor is honest on its own, and the SPL sensor's partners cover its blind spots exactly. Pair it first with the PIR motion sensor: PIR responds instantly but goes blind to anyone who sits still for thirty seconds, while sound persists as long as people do anything at all. Pair it next with the SCD41 CO2 sensor, and you get complementary timescales: sound and motion react within a second, while CO2 needs two to five minutes to rise and five to fifteen to fall. The fast pair proposes a state change; the slow one confirms or vetoes it. Out of this comes a five-state machine: EMPTY when motion is zero, CO2 is near 500 ppm, and the level is below 40 dB. LOW_OCCUPANCY, the silent exam hall, when there is no motion but the sound floor sits between 38 and 50 dB. OCCUPIED and ACTIVE as motion, CO2, and dB climb together. ANOMALY whenever the level exceeds 80 dB regardless of everything else. The third partner is the SCT-013 current clamp: a compressor that hums acoustically and draws eight amps is definitely running; hum without current, or current without hum, is a fault worth investigating. An agent runs this fusion through the gateway's MCP tools, querying all three time series aligned on the monotonic tick, and, unlike a hard-coded threshold, it can explain which evidence drove its classification.

## Slide 08.9: Capstone C3: Is This Space Comfortable by the Numbers?

**Slide content:**
- Question: is the study hall genuinely comfortable, and who or what is making it worse?
- Sensors: BME688 (IAQ, T, RH), SCD41 (CO2), DS18B20 (temperature points), SPL (acoustic comfort)
- Contradiction to resolve: thermal and air quality readings say "comfortable" while occupants complain; the noise channel often holds the answer
- Decision: a ranked list of comfort interventions with measured evidence, delivered as a weekly agent report
- Agent orchestration: `capture_experiment` for a two-week baseline, `annotate` for complaints, `validate_reading` before trusting any channel

**Narration:**
The capstone question sounds simple: is this study hall comfortable? Comfort standards such as ASHRAE 55 are mostly thermal, so the obvious approach is to log temperature and humidity and declare victory when they sit in range. Here is the contradiction this project is built around: the thermal numbers can be perfect while the room fails its occupants, and the acoustic channel is usually where the failure hides. A study hall at a flawless 24 degrees with CO2 under 800 ppm but a sustained 58 dB from a rattling air handler is not a comfortable room, and no thermometer will ever say so. The student team deploys four sensors: the BME688 for air quality, temperature, humidity, and pressure, the SCD41 for CO2 as the ventilation truth signal, cascaded DS18B20 probes for thermal uniformity across the space, and the SPL sensor for the acoustic dimension. The agent orchestrates the campaign through the MCP server: it starts a named two-week capture, prompts occupants through the deployment journal to log complaints the moment they happen, validates each channel against its sensor card before trusting it, and then aligns complaint timestamps against all four series. The deliverable is a decision: a ranked, evidence-backed list of interventions, perhaps fix the air handler mount before touching the thermostat, with the measured data to defend each ranking.
