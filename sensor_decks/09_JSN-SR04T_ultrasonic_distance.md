# Sensor 09: JSN-SR04T - Ultrasonic Distance / Level (SIM4, pulse-width)

## Slide 09.1: AI-First: The Old Way and the New Way

**Slide content:**
- Old way: someone climbs to the rooftop tank and looks inside
- New way: an AI watches the water level day and night, and acts
- The pump stops before overflow, starts before the taps run dry
- No more water spilling off the roof every morning
- You decide what "too full" and "too empty" mean; the AI enforces it

**Narration:**
How does a campus know how much water is in the rooftop tank? The old way is exactly what you imagine: somebody climbs up, lifts the lid, and looks. So tanks overflow every morning, because nobody climbs at dawn, and sometimes they run dry mid-afternoon, because nobody climbs twice a day. The new way puts a small distance sensor inside the tank lid, looking down at the water, and an AI watches that level day and night. Think of it as a fuel gauge for the building's water, read by a watcher who never sleeps. When the level nears the top, the pump is switched off before the first drop spills. When it nears the bottom, the pump starts before the taps go dry. The wasted water stops, and nobody climbs anything. Your role changes with it: you are the one who decides what counts as too full and too empty. The AI holds the line you drew, every hour of every day.

## Slide 09.2: AI-First: What the AI Must Know About This Sensor

**Slide content:**
- The AI reads the sensor's ID card before trusting a single number
- The card says: I measure distance with sound echoes, 20 cm to 4.5 m
- One warning: warm air speeds up sound, so hot afternoons shift the reading
- Another: "no echo" can mean an empty tank, or a broken sensor
- An AI that knows these limits asks better questions than one that does not

**Narration:**
This sensor measures distance the way a bat does: it sends a click of sound and times the echo. Simple, and mostly honest. But the AI must know where the honesty ends, and that is written on the sensor's ID card, the small file the AI reads first. The card lists the working range: nothing closer than 20 centimetres, nothing farther than four and a half metres. Then two warnings. First, sound travels faster through warm air, so on a hot afternoon the reading shifts slightly even though the water has not moved, like a steel tape measure that stretches a little in the sun. Second, sometimes no echo comes back at all, and that has two very different meanings: the tank may truly be past empty, or the sensor may have failed. A person would shrug at a missing reading. An AI that knows its senses treats it as a clue and checks: was the level trending down, or did it vanish mid-scale? Knowing the limits of your instruments is not a weakness. It is what makes the next reading worth trusting.

## Slide 09.3: The Agentic Pattern: One Sensor Corrects Another

**Slide content:**
- Pattern in one line: sensors check each other's work
- Like a friend who checks your sums: both are better together
- Warm air makes this ruler lie slightly; a thermometer fixes it
- The AI applies the correction automatically, every few seconds, forever
- You design the thinking; the AI does the watching

**Narration:**
The pattern this sensor adds to your collection: one sensor corrects another. In plain words, sensors check each other's work. Think of a friend who checks your sums before you hand in homework. You are both decent alone; together you are reliable. Our sound ruler has one known weakness: sound moves faster in warm air, so on a hot afternoon it reports the level a few centimetres off, with no change in the tank at all. Nearby sits a thermometer, another sensor from this kit. The AI knows the ruler's weakness, knows the thermometer holds the missing fact, and puts the two together: read the temperature, correct the distance, then decide. It applies that correction every few seconds, for months, and never gets bored of the arithmetic. No person would do that; no person should have to. Notice the roles. You decided the correction should exist. The AI carries it out endlessly. You design the thinking, the AI does the watching. Now let us meet the sensor itself.

## Slide 09.4: What It Is

**Slide content:**
- Time-of-flight ultrasonic ranger: emits a 40 kHz sound pulse, times the echo
- Distance = (echo time × speed of sound) / 2; sound travels approximately 343 m/s at 20 °C
- Waterproof IP67 transducer on a cable, separate from the electronics board
- Measures distance to any surface: water, a person, a bin's contents, a vehicle
- Non-contact: nothing touches the thing being measured, so nothing corrodes or contaminates
- Interface note: output is a timed pulse, not an analog voltage (detail on the technical card)

**Narration:**
How do you measure the water level in a tank without ever touching the water? The same way a bat finds a moth. The JSN-SR04T sends out a short burst of ultrasound at 40 kilohertz, well above human hearing, and then listens for the echo bouncing back from the nearest surface. Sound travels through air at roughly 343 metres per second at room temperature, so if the echo returns in 6 milliseconds, the surface is about one metre away: the pulse travelled there and back, so we halve the round trip. The electronics do this timing for us and present the result as a pulse whose width encodes the distance. Two design details make this particular sensor special in our kit. First, the transducer, the part that actually clicks and listens, is a sealed IP67 waterproof unit on the end of a cable, physically separate from the electronics board. It can live inside a humid, condensing water tank for a semester while its electronics stay dry. Second, the measurement is completely non-contact. Nothing touches the water, so nothing corrodes, nothing fouls, and nothing contaminates. That single property is why this sensor, rather than a float or an electrode, is our tool of choice for liquid level, and, pointed at a chair instead of a tank, for detecting a person who is sitting perfectly still.

## Slide 09.5: What It Does in Practice

**Slide content:**
- Liquid level: overhead water tanks, sumps, rainwater harvesting, fuel tanks, lab chemical storage
- Stationary occupancy: desk, carrel, and seat detection where PIR goes blind
- Waste management: bin fill level enables demand-driven collection rounds
- Parking and vehicles: bay occupancy, height checks at gates
- Queue measurement: distance to the last person gives queue length directly
- Physics instrument: speed of sound, Torricelli tank-draining, projectile experiments

**Narration:**
Where does a non-contact ranger get used? Anywhere the question is "how far, how full, or is something there". The flagship job is liquid level: mounted inside the lid of an overhead tank, facing down, the sensor reads the distance to the water surface, and simple arithmetic converts that to litres. The same trick works for sumps filling during heavy rain, rainwater harvesting tanks, diesel reserves for a generator, and laboratory chemical storage where electrodes corrode and floats jam. The second family of jobs is presence. A motion sensor goes blind to a person who sits still for thirty seconds; an ultrasonic sensor mounted above a desk simply measures 1.2 metres to an empty chair and 0.7 metres to an occupied one, motion or no motion. That resolves the single most cited failure mode in our occupancy projects. Third, resource logistics: a sensor inside a bin lid reports fill depth, so waste collection happens when bins are actually full rather than on a fixed round, and the same geometry reports whether a parking bay holds a car. Fourth, queues: pointed along a canteen queue, the distance to the nearest person maps directly to queue length. And finally, it is a genuinely good physics instrument: measuring the speed of sound, watching a tank drain to verify Torricelli's law, all with automatic data logging.

## Slide 09.6: Technical Card

**Slide content:**
- Measurand: distance, via ultrasonic time-of-flight at 40 kHz
- Range: 20 cm to 4.5 m; blind zone below approximately 20 cm
- Resolution approximately 3-5 mm; practical accuracy about ±1 cm (surface and temperature dependent)
- Supply: 5 V from the SIM's boost converter; transducer IP67, electronics board separate
- Output: trigger/echo pulse-width, not analog; SIM4 firmware uses GPIO pulse capture, not the ADC
- Packaged sensor dimensions: [PLACEHOLDER]
- Interface and connector details: [PLACEHOLDER: keyed harness part number]
- SIM assignment: SIM4; measurement takes ~26 ms, logged every 5 s

**Narration:**
The numbers that matter. The JSN-SR04T ranges from 20 centimetres out to about 4.5 metres; inside 20 centimetres it is blind, because the transducer is still ringing from its own transmit pulse when the echo arrives. Resolution is approximately 3 to 5 millimetres, and in practice you should trust it to about plus or minus one centimetre, since the echo strength depends on the target surface and the speed of sound drifts with temperature, a point we will return to on the fusion slide. It runs from the 5 volt rail that SIM4's boost converter already provides. Now an honest engineering note, and it matters: despite sitting in the analog SIM's slot, this is not an analog sensor. It does not output a voltage proportional to distance. Its native interface is a trigger line and an echo line, and the distance is encoded in how long the echo line stays high. The SIM4 firmware therefore reads it with GPIO pulse capture, timing the echo edges with interrupts, exactly the mechanism SIM3 uses to timestamp motion events, rather than with the analog-to-digital converter. The connector must carry those two GPIO lines. A full measurement takes about 26 milliseconds, and the firmware logs a reading every five seconds, which is far faster than any tank or chair changes state. Packaged dimensions and the keyed harness details are placeholders pending production hardware.

## Slide 09.7: Climate Change Applications

**Slide content:**
- Water security: overhead tank monitoring, pump-off above 90%, pump-on below 20%, ends routine overflow waste
- Leak detection: a slow level drop with the pump off is a leak, quantified in litres per hour
- Adaptation: sump and basement level as flood early warning during intensifying rain events
- Rainwater harvesting: measured collected volume per rain event proves system efficiency
- Groundwater-linked: per-building consumption data makes water budgets enforceable
- Fuel monitoring: generator diesel consumption per outage, a direct carbon line item

**Narration:**
Water is where climate change becomes personal, and this sensor is the kit's primary water instrument. Consider the overhead tanks on every Indian campus. They are filled by pumps on timers or by someone's memory, which means they routinely overflow, wasting both the water and the electricity that lifted it to the roof, or they run dry and shut a building down. One sensor inside the tank lid closes that loop: pump off above ninety percent, pump on below twenty percent, and every overflow becomes an avoidable, logged event. The same continuous level trace gives you something subtler: with the pump off overnight, the level should be flat. A slow, steady drop is a leak, and the trace tells you its size in litres per hour, which turns "we might have a leak somewhere" into a work order. On the adaptation side, the sensor watches the other direction: mounted at the ceiling of a basement or above a sump, a rising reading during intense rainfall is a flood early warning that triggers the transfer pump before equipment drowns, and intensifying cloudbursts are precisely what a warming atmosphere delivers. Rainwater harvesting tanks get honest efficiency numbers, measured volume collected per rain event against roof area and rainfall. Even the diesel tank feeding the backup generator becomes a carbon line item: level drop per outage is fuel burned, convertible directly to kilograms of CO2.

## Slide 09.8: Fusion Partners

**Slide content:**
- DS18B20: speed of sound depends on temperature, c ≈ 331.3 + 0.606 × T (m/s); agent applies the correction
- Uncompensated error: approximately 1.7% across a 10 °C swing, centimetres over metres
- Water level trace PCB: independent wet/dry confirmation; two signals must agree before a flood alarm
- SEN0193 soil moisture: tank outflow vs soil response closes the irrigation loop
- PIR: ultrasonic confirms stationary presence exactly where PIR is blind

**Narration:**
The most instructive fusion in the whole kit hides inside this sensor's own equation. Distance is echo time multiplied by the speed of sound, but the speed of sound is not a constant: it is approximately 331.3 plus 0.606 times the temperature in Celsius, metres per second. Between a 15 degree winter night and a 40 degree summer afternoon, that is nearly a five percent shift; even a modest 10 degree swing moves readings by about 1.7 percent, which is centimetres of phantom level change on a two-metre tank. The DS18B20 temperature sensor turns that error into a lesson: the agent reads both series through `query_timeseries`, applies the correction, and the student watches a systematic error vanish. That is sensor fusion at its most concrete, one sensor calibrating another's physics. The second partnership is redundancy: the RadioStudio water level trace PCB gives a binary wet/dry signal, so a basement flood alarm can demand agreement, rising ultrasonic level and a wet trace, before waking anyone at 2 a.m. One sensor triggering alone is flagged as a probable fault instead. Third, the SEN0193 soil moisture probe: tank level falling while soil moisture rises means irrigation is working; tank falling while soil stays dry means a burst line. And pointed at a chair, the ultrasonic covers the PIR's stationary-person blind spot, with the PIR confirming the moment of arrival and departure.

## Slide 09.9: Capstone C6: Where Does the Campus Water Actually Go?

**Slide content:**
- Question: can we account for every tank-litre, and where is it being lost?
- Sensors: JSN-SR04T (tank levels), water level trace (leak points), SEN0193 (irrigation soil response), 4-20 mA industrial transmitters (line pressure)
- Contradiction to resolve: consumption inferred from tank drops exceeds what taps and irrigation can explain
- Decision: a water balance for one building, with located losses and a costed fix list
- Agents: scheduled watchdog queries level trends nightly, annotates anomalies, drafts the weekly water balance

**Narration:**
The capstone asks a question the campus facilities office usually cannot answer: where does the water actually go? The team instruments one building's water path. JSN-SR04T sensors log the overhead tank and the ground sump. The bare-trace water level PCBs sit at historically damp spots, under the pump room and along the main corridor ceiling. SEN0193 probes watch the garden beds that the building's irrigation line feeds, and a 4-20 milliamp pressure transmitter on SIM4 watches line pressure. Then the accounting begins, and with it the contradiction this project is designed around: the tank level trace says the building draws, say, four thousand litres a day, but everything you can attribute, taps, toilets, irrigation events visible in the soil moisture data, sums to three thousand. Where is the missing quarter? A leak, an unmetered connection, an overflow the timer pump causes at 3 a.m., or a systematic sensor error such as an uncompensated temperature drift? The agent orchestrates the hunt: a scheduled watchdog queries every level series overnight through the MCP tools, checks each against its sensor card's plausibility bounds, applies the DS18B20 sound-speed correction, and annotates anything unexplained. Students adjudicate the agent's weekly draft water balance, confirm or refute its leak hypotheses on foot, and deliver the decision: a located, quantified loss list with a costed fix recommendation, defensible line by line.
