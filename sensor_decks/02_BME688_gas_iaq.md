# Sensor 02: BME688 - Gas / IAQ, Temperature, Humidity, Pressure (SIM2, I2C)

## Slide 02.1: AI-First: The Old Way and the New Way

**Slide content:**
- The old way: the room feels stuffy, someone finally opens a window
- The new way: an AI watches the air continuously and acts early
- Air tells on itself slowly: sleepy classes, slow headaches
- The AI notices the slide before people feel it
- Your role: design how the watcher thinks about air

**Narration:**
After lunch, a classroom slowly turns stuffy. Nobody notices while it happens; people just feel sleepy, and eventually someone opens a window. That is the old way: humans sensing air with their own comfort, and reacting late. The new way puts an AI on air duty. This sensor reports temperature, humidity, pressure, and the chemistry of the air many times a minute, and the AI watches that stream continuously. It notices the slow slide toward stuffiness half an hour before anyone yawns, and it can act: nudge a fan, open a vent, or alert the caretaker. Notice again that this is not an assistant waiting for your question. Nobody asks "is the air fine?" at the right moment; that is exactly the problem. The watcher must be on duty all the time, and the watcher must be designed. What it should watch, when it should act, and how sure it must be first: those choices are yours. This deck is about giving it good senses for air.

## Slide 02.2: AI-First: What the AI Must Know About This Sensor

**Slide content:**
- Surprise: there is already a tiny AI inside this chip
- It smells the air and estimates air quality
- An estimate is an opinion, not a fact
- The sensor card, its ID card, labels each number: measured or estimated
- An AI that knows the difference stays honest

**Narration:**
Now the surprise: there is already an AI inside this sensor. The BME688 smells the air. A tiny program inside it, trained by its maker Bosch, turns that smell into an air quality score and an estimated CO2 number. Estimated is the key word. The chip does not count CO2 molecules; it guesses the level from the smells it detects. A guess can be useful, and it can also be wrong, for example when someone opens a bottle of sanitiser nearby and the chip smells alcohol. So the honesty facts our AI must know are these: temperature, humidity, and pressure from this chip are measured, with known error. The air quality score and the CO2 figure are opinions. That distinction is written on the sensor card, the sensor's ID card that the AI reads. An AI that knows which numbers are opinions stays honest about them. An AI that does not will state a guess with full confidence, and you will believe it. What it is told is up to you.

## Slide 02.3: The Agentic Pattern: Adjudicating Two Witnesses

**Slide content:**
- The pattern: when two sensors disagree, judge, do not average
- Like two friends with different stories: ask who was there
- BME688 estimates CO2 from smells; SCD41 actually counts it
- Disagreement is a clue, not an error
- You write the judging rules; the AI applies them every minute

**Narration:**
The pattern this sensor teaches: Adjudicating Two Witnesses. Imagine two friends tell you different stories about the same event. You do not split the difference; you ask who was actually there. Sensors deserve the same treatment. Two devices in this kit will speak about CO2 in a room. The BME688 estimates it from smells. The SCD41, which you will meet later, actually counts CO2 molecules with light. When they disagree, averaging would be a mistake. The right move is to judge: the SCD41 was there; believe it, and treat the disagreement itself as a clue. Maybe fresh paint or a cleaning spray is in the room, and the BME688 is telling you that in its own way. Disagreement is information, not error. Here is the split of roles, and it repeats in every deck: you write the judging rules once, deciding which witness outranks which and when. The AI then applies those rules every minute, tirelessly, on live data. With both witnesses in mind, let us open up the chip itself.

## Slide 02.4: What Is the BME688?

**Slide content:**
- Four sensors in one 3 mm chip: temperature, humidity, barometric pressure, gas
- Gas sensing principle: heated metal-oxide surface changes conductivity when gas molecules react with it
- Gas resistance is the raw signal; software turns it into air-quality estimates
- Bosch BSEC library outputs IAQ index, estimated CO2 (eCO2), and breath-VOC equivalents
- Talks I2C on SIM2, sharing the bus with SCD41 and VEML7700

**Narration:**
Can one chip smaller than a grain of rice describe the air in a room? The BME688 comes close. It packs four sensing functions into a package about three millimetres on a side: temperature, relative humidity, barometric pressure, and gas. The first three use well-understood micro-machined structures. The gas sensor is the interesting one. A tiny plate inside the chip is heated to a few hundred degrees, and its surface is coated with a metal oxide. When volatile organic compounds, the gases released by paints, cleaning agents, cooking, and human breath, touch that hot surface, they react with the oxide and change its electrical conductivity. The chip reports that as a gas resistance value. Raw resistance is hard to interpret on its own, because it also depends on temperature and humidity, so Bosch supplies a software library called BSEC that applies corrections and outputs friendly quantities: an Indoor Air Quality index, an estimated CO2 level called eCO2, and a breath-VOC equivalent. Keep the word "estimated" in mind; we will return to it, because it is the most important lesson this sensor teaches. In the kit the BME688 connects over the I2C bus to SIM2, where it can share the same two wires with the SCD41 and the VEML7700. The SIM runs the Bosch algorithms and broadcasts the corrected values over BLE.

## Slide 02.5: What It Does in Practice

**Slide content:**
- Indoor air quality monitoring in homes, offices, schools, vehicles
- Weather sensing: pressure trends for short-term forecasting, humidity for comfort
- Gas leak and smell detection: solvents, spoiled food, smoke precursors
- Trainable: BME AI-Studio lets the gas sensor learn specific smell signatures
- Found in consumer air purifiers, smart thermostats, wearables

**Narration:**
What is this sensor's day job? Mostly, telling buildings about their own air. Air purifiers use chips of this family to decide when to speed up the fan. Smart thermostats use the temperature and humidity channels for comfort control. Weather enthusiasts use the pressure channel, because a falling pressure trend over a few hours is still one of the most reliable short-term storm signals available without a satellite. The gas channel earns its keep in scenarios where "something is in the air" matters more than knowing exactly what: solvent fumes in a workshop, spoiled food in a pantry, smoke-adjacent compounds before an alarm would trigger. There is also a genuinely modern capability here: the BME688's gas sensor can be operated with varying heater temperature profiles, and Bosch's AI-Studio tool lets you train a small machine-learning model to recognise specific smell signatures, distinguishing, say, fresh coffee from burnt coffee. That makes it one of the few sensors in this kit with a learnable front end. For our purposes the headline applications are indoor air quality and environmental context: it is the kit's general-purpose "state of the air" instrument, providing the temperature, humidity, and pressure corrections that several other measurements in this course quietly depend on.

## Slide 02.6: Technical Card

**Slide content:**
- Measurands: temperature (-40 to +85 °C, ±1 °C), humidity (0-100 %RH, ±3 %RH), pressure (300-1100 hPa, ±0.6 hPa), gas resistance (ohms)
- Derived by BSEC: IAQ index 0-500, eCO2 (ppm, estimated), bVOC (ppm equivalent)
- Original package: 3.0 × 3.0 × 0.9 mm metal-lid LGA, magnified in photos
- Output: digital, I2C (address 0x76 in this kit) or SPI; kit uses I2C
- eCO2 is inferred from VOCs, not a CO2 measurement
- Packaged sensor dimensions: [PLACEHOLDER]; connector: [PLACEHOLDER]; SIM2, I2C

**Narration:**
The technical card for the BME688 is longer than most because it reports many quantities, and they do not all deserve equal trust. The directly measured channels are solid: temperature from minus 40 to plus 85 degrees with roughly ±1 degree accuracy, humidity across the full range with about ±3 percent accuracy, and pressure from 300 to 1100 hectopascals with ±0.6 hectopascal accuracy, good enough to resolve a two-storey height change. The gas channel reports resistance in ohms, and the BSEC library converts that into an IAQ index from 0 to 500, an eCO2 value in ppm, and a breath-VOC equivalent. Here is the line on this slide that matters most: eCO2 is estimated, not measured. The chip cannot see CO2 molecules at all; it infers a plausible CO2 level from VOC patterns, on the assumption that people are the dominant source of both. When that assumption fails, and it often does, eCO2 is wrong with full confidence. The kit deliberately includes the SCD41, which measures CO2 photoacoustically, as the truth reference, and comparing the two is a formal validation exercise. The raw chip is a three-millimetre LGA package; it speaks I2C at address 0x76 in our wiring. The packaged sensor dimensions and connector details are placeholders pending the production packaging documents. It connects to SIM2.

## Slide 02.7: Climate Change Applications

**Slide content:**
- Ventilation efficiency: healthy air with minimum energy is a core mitigation problem
- Humidity + temperature: heat index, the variable that determines human heat stress
- Pressure: hyperlocal weather trends, storm and monsoon onset context
- Wildfire and biomass smoke: VOC channel as an early smoke-context signal
- Baseline air quality campaigns where reference stations do not exist

**Narration:**
How does a room-scale air sensor connect to a planet-scale problem? Through ventilation, heat stress, and smoke. Ventilation first: buildings spend enormous energy conditioning air, and the mitigation question is always "how little outside air can we condition while keeping the air healthy?" Answering it requires continuous air-quality measurement, which is exactly what this chip provides cheaply and everywhere. Heat stress second: climate adaptation planning increasingly runs on the heat index, the combination of temperature and humidity that determines what the human body can actually endure. A dry 38 degrees is survivable; a humid 34 degrees can be dangerous. The BME688 measures both variables in one device, so a student can compute wet-bulb-adjacent stress indicators for a real classroom during a real heat wave. Pressure gives hyperlocal weather context: pressure trends anchor rainfall and storm-onset observations in field campaigns. And the VOC channel has a serious climate role as a smoke-context signal: biomass burning and wildfire smoke carry VOC loads that this sensor responds to minutes before a person complains, useful in regions where crop-residue burning drives seasonal air crises. Finally, in most of the world there is no reference air-quality station within tens of kilometres. A distributed set of these sensors does not replace reference instruments, but it maps where and when the problem is worst, which is where policy starts.

## Slide 02.8: Fusion Partners

**Slide content:**
- SCD41: the truth test; measured CO2 versus estimated eCO2, a built-in validation lab
- PIR: attributes air-quality changes to occupancy versus other sources
- SPL: separates "many quiet people" from "few noisy machines" in IAQ interpretation
- VEML7700: lux drop plus humidity rise equals fog, not cloud; weather disambiguation
- Agent role: validate_reading plus cross-sensor queries expose where BSEC estimates break

**Narration:**
The BME688's best fusion partner is the sensor designed to embarrass it. Put the SCD41 beside it and log both: the SCD41 measures CO2 directly, the BME688 estimates eCO2 from VOCs. In a room where people are the only emission source the two track each other respectably. Now open a bottle of hand sanitiser. The eCO2 will spike while the measured CO2 does nothing, and the student has just watched an algorithm confuse alcohol vapour with human breath. That single experiment teaches more about sensor trust than any lecture, and it is why the two sensors share SIM2's I2C bus by design. The PIR adds attribution: if IAQ degrades while the PIR shows an empty room, the source is not people, so look for solvents, cooking, or outdoor infiltration. The SPL sensor refines that further, separating a full silent classroom from a loud empty corridor. The VEML7700 pairing is subtler and elegant: a simultaneous lux drop and humidity rise means fog rather than cloud cover, a distinction one sensor alone cannot make. The agent runs these cross-checks through the MCP tools: validate_reading applies each sensor card's plausibility bounds, and a timeseries query joined on the monotonic tick lets the model say not just "IAQ worsened" but "IAQ worsened, the room was empty, and measured CO2 was flat, so suspect a chemical source."

## Slide 02.9: Capstone C3

**Slide content:**
- Question: is this space comfortable by the numbers?
- Sensors: BME688, SCD41, DS18B20, SPL
- Contradiction to resolve: sensors disagree; eCO2 says bad air, SCD41 says fine
- Decision: publish a defensible comfort verdict per room, with evidence
- Agents run scheduled comfort audits and flag standard violations with reasoning

**Narration:**
Capstone C3 asks a deceptively simple question: is this space comfortable by the numbers? Pick a study hall or classroom people actually complain about. Deploy the BME688 for temperature, humidity, pressure, and IAQ; the SCD41 for measured CO2; a DS18B20 as an independent temperature reference; and the SPL sensor for the acoustic dimension of comfort that air sensors ignore. Comfort standards give you the numeric targets: roughly 23 to 26 degrees, 40 to 60 percent humidity, CO2 under 1000 ppm, background noise under about 45 dB for study spaces. The contradiction is guaranteed to appear: some week the BME688's eCO2 will scream while the SCD41 sits at 600 ppm, or the two temperature sensors will disagree by more than their combined error bands because one sits in sunlight. Your job is not to average the disagreement away but to adjudicate it: which sensor do you believe, and what evidence makes that belief defensible? The deliverable is a comfort verdict for the room, per hour of the day, with every claim traceable to data. The agent does the heavy lifting on schedule: a watchdog agent queries the timeseries daily, checks each channel against the standards and the sensor cards, and writes an annotated report. The student's role is the one the model cannot take: deciding whether the verdict survives scrutiny, and what the building should change because of it.
