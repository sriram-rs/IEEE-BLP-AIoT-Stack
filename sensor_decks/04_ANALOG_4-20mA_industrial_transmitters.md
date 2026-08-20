# Sensor 04: Analog 4-20 mA Industrial Transmitters (SIM4, Analog)

## Slide 04.1: AI-First: The Old Way and the New Way

**Slide content:**
- The old way: a person squints at a flat chart and guesses
- The new way: an AI watches the sensor's wire, continuously
- Industrial sensors sit far away, on long cables, in harsh places
- A flat reading could be calm weather, or a dead sensor
- The watcher must be able to tell the difference

**Narration:**
Industrial measurement has a distance problem. The wind sensor is on the roof, the tank sensor is in the basement, and the person who cares about the readings is somewhere else entirely, looking at a chart. In the old way, when that chart goes flat, a person squints at it and guesses: has the wind really stopped for three days, or did something break? Often the guess is wrong, and the error sits in the data for weeks. The new way hands the watching to an AI, and gives it something a chart never shows: knowledge of the wire itself. Industrial sensors of this family speak over long cables, through heat and dust and electrical noise, and things do break out there. So the question this deck opens with is blunt: when the signal says nothing is happening, how does the watcher know whether to believe it? The answer, invented sixty years ago, is one of the cleverest tricks in engineering, and it is why this old standard fits an AI-first course so naturally.

## Slide 04.2: AI-First: What the AI Must Know About This Sensor

**Slide content:**
- These sensors send readings as current: 4 to 20 milliamps
- Zero wind is sent as 4, never as 0
- So 0 can only mean one thing: the wire is broken
- Like a guard who calls in hourly, even to say all quiet
- The sensor's ID card teaches the AI this rule

**Narration:**
Here is the sixty-year-old trick. These sensors send their reading as a small electric current, between 4 and 20 milliamps. The scale is deliberately strange: zero wind is sent as 4 milliamps, never as 0. Why waste the bottom of the scale? Because then 0 can only mean one thing: the wire is broken. The signal behaves like a guard who calls in every hour even when nothing has happened. As long as the calls come, quiet means quiet. The moment the calls stop, you know the guard is in trouble; you do not conclude the night was peaceful. This rule is exactly what the AI must know, and it is written on the sensor card, the sensor's ID card that the AI reads. With it, the AI can never log a broken cable as three days of calm weather, and never mistake a dead sensor for a quiet world. Without it, the AI would do what people do: look at zero and invent a story. Knowing how a sensor fails is knowledge just as precious as knowing how it measures.

## Slide 04.3: The Agentic Pattern: Design for the Failure Path

**Slide content:**
- The pattern: decide in advance what breaking looks like
- "No new messages" is not the same as "phone switched off"
- A healthy zero must look different from a broken wire
- Out-of-range signals are faults to report, never data to chart
- You design the failure signs; the AI keeps watch for them

**Narration:**
The pattern this deck adds: Design for the Failure Path. In one sentence: decide in advance what breaking looks like, so it can never be mistaken for data. Your phone shows the idea nicely. A phone that says no new messages and a phone that is switched off are both silent, but they are two completely different situations, and you can tell them apart at a glance. Good sensor systems are built the same way. The current loop keeps its healthy zero at 4 milliamps, so a broken wire, at 0, looks broken. Our kit copies this idea everywhere: every sensor's radio message carries a small health flag and a message counter, so a dead sensor announces itself instead of quietly disappearing. And the AI is instructed to treat anything out of range as a fault to report, never as a reading to chart. The roles are the usual ones: you design what failure looks like; the AI keeps watch for it, day and night. Ask this of every system you ever build: where is its zero milliamps? Now, the standard itself.

## Slide 04.4: What Is a 4-20 mA Transmitter?

**Slide content:**
- Not one sensor: an industrial signalling standard that thousands of sensors speak
- The measured value is encoded as a current, 4 mA = bottom of range, 20 mA = top
- Current, unlike voltage, survives long cables without loss
- 4 mA as "live zero": 0 mA means the loop is broken, a built-in fault alarm
- Worked example in this kit: cup anemometer, 0-30 m/s mapped to 4-20 mA
- SIM4 converts loop current to voltage with a burden resistor, then digitises

**Narration:**
This deck is different from the others: the sensor here is really a language. The 4-20 milliamp current loop is the standard way industrial sensors have reported measurements for over sixty years, and thousands of instruments speak it: pressure transmitters, level gauges, flow meters, and the wind sensor we use as our worked example. The idea is simple and clever. Instead of encoding the measurement as a voltage, the transmitter regulates the current flowing through a two-wire loop. Four milliamps means the bottom of the measurement range; twenty milliamps means the top; everything between is a straight line. Why current instead of voltage? Because a voltage sags along a long cable as the wire's own resistance eats it, but the current in a loop is the same at every point of the loop, whether the cable is two metres or two kilometres. That is why factories trust it. And why start at four rather than zero? Because zero is reserved for disaster. A healthy loop never carries less than 4 mA, so if the receiver ever sees zero, the wire is cut or the transmitter is dead. The signal carries its own health certificate, a live zero. Our example instrument is a cup anemometer: wind spins the cups, and the electronics map 0 to 30 metres per second onto 4 to 20 milliamps for SIM4 to read.

## Slide 04.5: What It Does in Practice

**Slide content:**
- The wiring backbone of process industry: refineries, water plants, factories, HVAC plants
- Typical transmitters: pressure, level, flow, temperature, wind, pH, vibration
- Anemometer example: cup rotation rate proportional to wind speed
- Two-wire loops can power the transmitter from the same pair that carries the signal
- Learning one loop means being able to read almost any industrial instrument

**Narration:**
Walk into any water treatment plant, refinery, dairy, or large building's HVAC plant room, and the instruments on the walls are overwhelmingly 4-20 mA devices. A pressure transmitter on a pipe, a level transmitter on a tank, a flow meter on a main, a pH probe in a treatment basin: different physics at the sensing tip, identical electrical behaviour at the wire. That uniformity is the point. A plant engineer can wire, test, and fault-find any of them the same way, and so can you. Many transmitters go further and draw their own operating power from the same two wires that carry the signal, which is why a single twisted pair can run from a control room to a sensor hundreds of metres away with nothing else attached. Our worked example, the cup anemometer, shows the full chain. Wind pushes three cups mounted on a rotor; the rotation rate is very nearly proportional to wind speed; internal electronics count the rotation and drive the loop so that a dead calm reads 4 mA and a 30 metre-per-second gale reads 20 mA. The instrument needs a 12 volt supply, which the SIM provides from its boost converter. Master this one instrument and you have effectively learned the interface of an entire industry: next semester's flow meter or level transmitter is the same loop with a different label on the range.

## Slide 04.6: Technical Card

**Slide content:**
- Standard: 4-20 mA current loop; linear mapping, transmitter-defined range
- Example instrument: cup anemometer, 0-30 m/s, 12 V supply, accuracy approximately ±0.5 m/s [PLACEHOLDER: confirm per datasheet]
- SIM4 front end: precision burden resistor converts 4-20 mA to a voltage within ADC range
- Live-zero fault detection: current below 4 mA flagged as loop fault, not as a reading
- Mounting: upright, rigid, unobstructed rotation; cable strain-relieved
- Packaged dimensions: [PLACEHOLDER]; connector: [PLACEHOLDER]; SIM4, Analog

**Narration:**
The technical card here describes two things at once: the standard and the example instrument. The standard first. The loop carries 4 to 20 milliamps, linearly mapped across whatever range the transmitter defines; the mapping lives in the sensor card on the gateway, so the same SIM4 firmware serves any loop instrument, and adding a new transmitter means publishing a new card, not writing new code. SIM4's front end is a precision burden resistor: the loop current flows through it, producing a voltage the ESP32's ADC can digitise. The firmware then applies the reverse mapping to engineering units. Below 4 mA, the firmware does something important: it refuses to report a number. Current under the live zero means a broken wire, a dead transmitter, or a power fault, so the SIM raises the sensor-fault status bit instead of publishing a plausible-looking wind speed of zero. Silent garbage is exactly what this architecture is designed to prevent. The example instrument is the cup anemometer: range 0 to 30 metres per second, supplied at 12 volts from the SIM's boost converter, accuracy in the region of half a metre per second, to be confirmed against the production datasheet. Mechanical care dominates its error budget: mount it upright and rigid, keep the rotation path clear, and strain-relieve the cable. The packaged dimensions and keyed connector details are placeholders pending production documents.

## Slide 04.7: Climate Change Applications

**Slide content:**
- Wind resource assessment: siting decisions for wind generation start with anemometry
- Weather stations: wind speed is a core observational variable
- Heat and comfort: wind modifies perceived temperature and building ventilation strategy
- The loop standard generalises: flow meters for water audits, level and pressure for infrastructure
- Teaches the instrumentation grammar of industrial decarbonisation

**Narration:**
Wind measurement earns its climate credentials twice, once as energy and once as weather. On the energy side, every wind turbine ever sited was preceded by an anemometer. Wind power grows with roughly the cube of wind speed, so the difference between a site averaging five metres per second and one averaging six is not twenty percent more energy but closer to seventy. Long-duration, honest wind records are therefore the foundation of wind resource assessment, and a student who runs a semester-long campaign on a rooftop is performing a small version of exactly that study. On the weather side, wind speed is a core variable of every meteorological station, and changing wind patterns are themselves a fingerprint of the changing climate. Wind also shapes adaptation decisions closer to home: it modifies how hot a hot day feels, and it determines when natural ventilation can replace air conditioning, a direct energy decision this kit can inform by fusing wind with indoor sensors. Step back from the anemometer, though, and the larger climate value is the standard itself. Decarbonising industry means instrumenting it, and the instruments of water audits, district cooling, and process efficiency, the flow meters, level gauges, and pressure transmitters, overwhelmingly speak 4-20 mA. A student fluent in this loop can walk into that world and read its dials.

## Slide 04.8: Fusion Partners

**Slide content:**
- VEML7700 plus BME688: wind, light, humidity, pressure combine into a campus micro-weather station
- SEN0193: wind-driven evapotranspiration context for irrigation decisions
- JSN-SR04T on the rain tank: wind and rainfall harvesting correlated
- SCT-013: wind resource versus energy demand profiles, matched or mismatched
- Agent role: capture_experiment builds multi-variable weather datasets aligned on tick_ms

**Narration:**
An anemometer alone gives you a wind log; fused with the rest of the kit it gives you a weather understanding. Combine it with the VEML7700 for light and the BME688 for humidity, temperature, and pressure, and four packaged sensors become a genuine campus micro-weather station, logging the variables that matter for both comfort and energy. The pairing with the SEN0193 soil moisture sensor answers a question every gardener asks without instruments: how fast is the ground drying? Wind is a principal driver of evapotranspiration, so a windy dry week and a still humid week demand different irrigation, and an agent that sees both series can schedule watering with reasons attached. Add the JSN-SR04T on a rainwater tank and you can correlate harvest with the weather that produced it. The SCT-013 pairing is the energy-planner's view: log wind resource and electrical demand side by side for a month, and ask whether they rise together or oppose each other, the exact question that determines how useful a small wind installation would be at your site. The agent orchestrates all of this through capture_experiment, recording named multi-sensor datasets aligned on the monotonic tick, and through the deployment journal, where the annotate tool records what the numbers cannot know: the anemometer's mast height, nearby obstructions, the day the mounting was moved.

## Slide 04.9: Capstone C6

**Slide content:**
- Question: where does the campus water actually go?
- Sensors: JSN-SR04T on the overhead tank, water level PCB, SEN0193, 4-20 mA instruments (anemometer now, flow/level transmitters as the growth path)
- Contradiction to resolve: tank level falls faster than metered or expected use
- Decision: a pump schedule and a leak verdict, with measured evidence
- Agents assemble the balance sheet; the live-zero teaches fault-versus-reading discipline

**Narration:**
Capstone C6 asks a question campus facilities teams answer today by climbing tank ladders: where does the water actually go? The JSN-SR04T measures the overhead tank level continuously, which yields consumption rate. The water level PCB watches for overflow at the tank lip and for flooding at ground level. The SEN0193 tracks irrigation moisture in the planted areas that receive part of the water. The 4-20 mA channel is this deck's contribution, in two stages: today, the anemometer supplies the weather context that drives evaporation and irrigation demand; as the platform grows, the same SIM4 loop interface accepts industrial flow and pressure transmitters, the instruments a real water audit would add next, with nothing but a new sensor card. The contradiction that drives the project: the tank level falls faster than any accounted use explains. Is it a leak, an unmetered draw, evaporation, or a sensor fault? The students must argue from evidence: night-time level decay with pumps off is the classic leak signature. The live-zero discipline runs through the whole exercise: a loop reading below 4 mA, or an ultrasonic echo that never returns, must be treated as a fault to investigate, never as a zero to average in. The agent assembles the water balance sheet from aligned timeseries and drafts the verdict; the class defends or overturns it, and the deliverable is a pump schedule and a leak decision the facilities team could act on Monday morning.
