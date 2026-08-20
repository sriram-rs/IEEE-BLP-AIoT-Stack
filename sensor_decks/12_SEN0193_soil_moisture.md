# Sensor 12: DFRobot SEN0193 - Soil Moisture (SIM4, Analog)

## Slide 12.1: AI-First: The Old Way and the New Way

**Slide content:**
- The old way: a person checks a reading and decides to water
- The new way: an AI watches the soil for you, day and night
- When the bed runs dry, the AI can start the watering itself
- Like a garden caretaker who never sleeps
- This deck: soil moisture as something an AI senses and acts on

**Narration:**
Who is going to read this soil sensor? The old answer: you. You look at a number, judge whether the bed looks thirsty, and water it. It works, as long as you remember, and as long as you are there. The new answer in this course: an AI reads it for you. Think of it as a caretaker who never sleeps. It watches the soil all day and all night, and when the bed runs dry it can start the watering itself. You may be away for a week; the garden does not mind, because the caretaker is still on duty. That is the shift this whole course keeps making, and it is worth saying slowly. The sensor is no longer an instrument for your eyes. It is a sense organ for an AI, one that perceives the garden continuously and acts on what it perceives. But a caretaker is only as good as their knowledge of the tools they hold. What must the AI know about this probe before we trust it with our garden? That is the next slide.

## Slide 12.2: AI-First: What the AI Must Know About This Sensor

**Slide content:**
- An AI is only as good as what it knows about its senses
- It reads the sensor's ID card: what the probe says, how it fails
- The probe reports a voltage, not a moisture percentage
- Pulled out of the soil, it looks like a sudden drought
- Its numbers mean nothing until it learns its own dry and wet points

**Narration:**
How far should the AI trust this probe? Exactly as far as the probe deserves, and not a centimetre further. To get that right, the AI reads the sensor's ID card, a small file that travels with the probe and tells the truth about it. Three truths matter here. First, the probe does not speak in moisture percentages; it speaks in volts, and someone has to say what those volts mean. Second, the probe can mislead without lying: pull it out of the soil, and the readings look exactly like a drought that began that very minute. The ID card lists this, so the AI can suspect the hardware before it blames the weather. Third, and biggest of all: this probe's numbers mean nothing until it has learned its own two reference points, what it reads bone dry, and what it reads soaking wet. An AI that knows all this reads the probe with judgment. One that does not is only guessing, confidently. That third truth is so important that it is this sensor's pattern, and it comes next.

## Slide 12.3: The Agentic Pattern: No Meaning Without Calibration

**Slide content:**
- The pattern: a raw number means nothing without a reference point
- Like scoring 43 marks without knowing the maximum
- The probe first learns its own "bone dry" and "soaking wet" readings
- The AI guides you through the teaching: hold in air, dip in water, done
- You design the thinking; the AI does the watching

**Narration:**
Every sensor in this course teaches one way of thinking, one pattern. This probe's pattern is called No Meaning Without Calibration. Here is the idea in one line: a number without a reference point is just a number. Suppose I tell you that you scored 43 marks. Happy? You cannot say, because I did not tell you the maximum. 43 out of 50 and 43 out of 200 are different stories. This probe has the same problem. It reports 1.8 volts. Is that wet or dry? Nobody knows, not even the smartest AI, until this particular probe learns its own two reference points: what it reads held up in dry air, and what it reads dipped in a glass of water. The pleasant surprise is who does the teaching. The AI walks you through it as a short conversation: hold the probe in the air, now dip it, thank you, saved. After that, every reading has meaning. You designed the thinking; from here the AI does the watching. With that idea in hand, let us meet the probe itself.

## Slide 12.4: What It Is

**Slide content:**
- A capacitive soil moisture sensor: it measures how much water is in the soil without any metal touching the soil
- Water changes the dielectric constant of soil; dry soil is approximately 3-5, water is approximately 80
- The probe is a flat PCB paddle; its copper sensing pad forms one plate of a capacitor, the surrounding soil completes it
- A 555-style oscillator on the probe converts capacitance to a smooth analog voltage, 0 to approximately 3.0 V
- More water means higher capacitance, which means a lower output voltage
- No exposed electrodes: the sensing area is covered by solder mask, so nothing corrodes

**Narration:**
How do you ask the soil how thirsty it is? You cannot see moisture below the surface, and squeezing a handful of soil does not scale to a garden, a green roof, or a farm. The SEN0193 answers the question electrically. It exploits a large physical contrast: dry soil has a dielectric constant of roughly 3 to 5, while water sits near 80. That is more than a tenfold difference, which makes the measurement robust. The probe is simply a printed circuit board shaped like a paddle. A copper pad inside the board acts as one plate of a capacitor, and the soil around the paddle acts as the rest of the capacitor. As water content rises, the capacitance rises with it. A small oscillator circuit, built around the classic 555 timer topology, converts that capacitance into a DC voltage between zero and approximately three volts. Wetter soil produces a lower voltage. Notice what is not here: no bare metal electrodes, no current flowing through the soil. The sensing surface is sealed under solder mask. That single design decision is why this sensor survives a full semester buried outdoors, and it is the first thing we will compare against the older resistive approach.

## Slide 12.5: What It Does in Practice

**Slide content:**
- Irrigation scheduling: water when the root zone is dry, skip when it is not
- Container and greenhouse growing: per-pot moisture monitoring
- Green roofs and vertical gardens: confirm the substrate is holding design moisture
- Lawn and grounds management: detect overwatering, the most common failure
- Research and teaching: drought stress experiments, infiltration studies
- Why capacitive wins outdoors: resistive probes corrode electrolytically and drift within weeks; this probe holds calibration for a season

**Narration:**
Where does a sensor like this earn its keep? Anywhere a human currently guesses about watering. The most common use is irrigation scheduling: instead of watering on a timer, you water when the root zone actually needs it. Greenhouses and nurseries put one probe per bench or per large container. Green roof operators use them to verify that the growing substrate holds the moisture the design assumed. Turf managers use them to catch the most frequent real-world failure, which is overwatering, not underwatering. And in research settings, they instrument drought stress and infiltration experiments. A fair question: why not use the cheaper resistive probe, the one with two exposed metal prongs? Because passing current through wet soil electrolyzes the metal. The prongs oxidize, the readings drift within two to three weeks, and outdoors the probe is effectively consumable. The SEN0193 measures capacitance through a sealed surface, so no ions flow and nothing corrodes. For a course where your deployment must survive weeks in a planter and still produce comparable data at the end, that difference is decisive. This is a recurring lesson of the kit: the sensing principle determines the maintenance burden, and the maintenance burden determines whether the data is trustworthy months later.

## Slide 12.6: Technical Card

**Slide content:**
- Measurand: volumetric soil moisture, reported as a calibrated 0-100 percent scale
- Raw range: analog 0 to approximately 3.0 V (dry reads high, saturated reads low)
- Accuracy: no absolute vendor spec; after two-point calibration, repeatability is approximately ±3-5 percent of scale (moderate confidence)
- Supply: 3.3-5.5 V, approximately 5 mA; powered from the SIM rail
- Original form: single PCB module, approximately 98 x 23 mm probe
- Packaged sensor dimensions: [PLACEHOLDER]
- Interface/connector details: [PLACEHOLDER: keyed harness part number]
- SIM assignment: SIM4, analog ADC input

**Narration:**
Here is the engineering identity of the sensor, the same facts the gateway serves to an AI agent as a sensor card. The measurand is volumetric soil moisture, delivered as a raw analog voltage between zero and approximately three volts. The vendor publishes no absolute accuracy figure, and that is honest: absolute soil moisture depends on soil type, compaction, and temperature. What you can rely on is repeatability after calibration, approximately plus or minus three to five percent of scale. Two practical caveats matter. First, the ESP32's internal ADC is nonlinear near the top of its range, above approximately 3.0 volts. The SIM4 design keeps the dry-air reading below 2.8 volts using a divider, or the attenuated input path, so the dry end of the scale stays in the linear region. Second, the calibration itself: the SIM stores two reference points in non-volatile memory, the reading in dry air and the reading in saturated soil or water. Every field reading is mapped between those two anchors. The packaged sensor dimensions and the keyed connector details are placeholders for now and will be supplied with the production enclosure. On the platform, this probe connects to SIM4, the analog interface module, which digitizes the voltage, applies the stored calibration, and broadcasts the percentage over BLE.

## Slide 12.7: Climate Change Applications

**Slide content:**
- Irrigation is approximately 70 percent of global freshwater withdrawals; scheduling from measured moisture saves 30-50 percent of irrigation water
- Adaptation: drought monitoring networks, early warning for crop stress
- Urban heat and stormwater: green roofs and rain gardens only perform when substrate moisture is managed
- Soil health: chronic overwatering drives nutrient runoff and nitrous oxide emissions
- Measurement role: ground truth for satellite soil moisture products at a single field point

**Narration:**
Why does a soil probe belong in a climate change course? Start with the largest number in the story: irrigation accounts for approximately seventy percent of global freshwater withdrawals. Field studies of sensor-driven irrigation repeatedly show thirty to fifty percent water savings compared with timer-based schedules, simply because timers water whether or not the soil needs it. As rainfall becomes more erratic, that efficiency stops being an optimization and becomes adaptation. The same probe supports drought monitoring: a network of cheap capacitive sensors shows how fast the root zone dries after rain, which is early warning for crop stress weeks before plants visibly wilt. Cities enter the picture through green infrastructure. Green roofs, rain gardens, and bioswales moderate urban heat and absorb storm surges, but only if their growing substrate is kept in a working moisture band; a dried-out green roof is just gravel with extra steps. There is also an emissions angle that surprises people: chronically saturated soil is a source of nitrous oxide, a greenhouse gas roughly 270 times more potent than CO2 per kilogram, so avoiding overwatering is itself mitigation. Finally, measurement. Satellites estimate soil moisture over kilometres; your probe measures one point honestly. Ground truth at known points is what makes the satellite products usable.

## Slide 12.8: Fusion Partners

**Slide content:**
- VEML7700 (lux): light dose drives evaporation; agent computes daily light integral alongside moisture decline
- DS18B20 + BME688 (temperature, humidity): together they form an evapotranspiration proxy; agent predicts tomorrow's moisture, not just today's
- JSN-SR04T (tank level): soil demand on one side, water supply on the other; agent closes the full irrigation loop
- Water level trace PCB: detects overflow or runoff at the drainage point, catching overwatering the soil probe misses
- Agent inference via MCP: query_timeseries across all streams, aligned on tick_ms, then a watering decision with stated confidence

**Narration:**
A moisture reading alone tells you the present. Fusion tells you the future, and the future is when you should water. Pair the probe with the VEML7700 light sensor and the agent can integrate the day's light dose; bright days pull water out of soil faster. Add DS18B20 temperature and BME688 humidity and you have the ingredients of an evapotranspiration estimate, the standard agronomic model of water loss. Now the agent is not reporting that soil is at forty percent; it is forecasting that the bed will cross the wilting threshold by Thursday afternoon, and it can defer watering if the pressure trend from the BME688 suggests rain. On the supply side, the JSN-SR04T ultrasonic sensor watches the irrigation tank. Soil demand and tank supply, held in the same database, let an agent answer the complete question: should we water, with what, and do we have enough? Finally, the bare-trace water level PCB at the drainage outlet catches the failure the soil probe cannot see: water pouring straight through and running off. In the MCP architecture, an agent calls query_timeseries on all of these streams, reconciled on the monotonic tick, and returns a watering decision with its reasoning and confidence attached, not just a chart.

## Slide 12.9: Capstone C7: When Should We Water, and Did It Work?

**Slide content:**
- Question: when should this planted bed be watered, and did the policy actually save water?
- Sensors: SEN0193 (moisture), VEML7700 (light), DS18B20 (temperature), BME688 (humidity, pressure)
- Contradiction to resolve: soil reads dry but rain is likely, or reads wet immediately after watering while the root zone below is still dry
- Baseline week on a fixed schedule, intervention weeks on agent-recommended watering; compare litres used and plant condition
- Edge loop: LLM authors a deterministic watering rule; cloud loop: agent reviews the week and revises the rule
- Decision at the end: adopt, revise, or reject the sensor-driven schedule, with measured evidence

**Narration:**
The capstone puts the sensor to work on a question with a measurable answer: when should we water, and did it work? Students instrument a real planted bed with the moisture probe in the root zone, light, temperature, and humidity alongside. Week one is the baseline: water on a fixed schedule, log everything, record the litres used. Then the agent takes over recommending: each morning it queries the aligned time series and proposes water or wait, with reasoning. The design forces students to confront contradictions. The surface probe reads wet minutes after watering while deeper soil is still dry, so where should the probe sit, and should there be two? The soil reads dry but falling pressure suggests rain within a day, so does the agent gamble on the forecast? Resolving these is the actual learning. The architecture lesson is the two loops. The agent does not open a valve at runtime; it authors a small deterministic rule, moisture below threshold and no rain signal means irrigate at dawn, and that rule runs on the edge device even if the cloud link drops. At semester's end the deliverable is a decision, not a dashboard: adopt, revise, or reject the sensor-driven schedule, defended with measured litres, plant condition, and an honest account of where the model was wrong.
