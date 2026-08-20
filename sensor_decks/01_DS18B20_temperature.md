# Sensor 01: DS18B20 - Temperature (SIM1, One-Wire)

## Slide 01.1: AI-First: The Old Way and the New Way

**Slide content:**
- The old way: you read the thermometer and decide
- The new way: an AI watches the temperature for you, continuously
- The AI can look up this sensor, question it, and double-check it
- It never sleeps, never forgets, never gets bored
- Your role changes: from reader of numbers to designer of thinking

**Narration:**
Think of the last time you looked at a thermometer. You read the number, you decided, maybe you switched the fan on. That is the old way: a person reads a number, a person decides. This course flips it. An AI watches this temperature for you, all day and all night, and it can act on what it sees: switch the fan, raise an alert, or simply make a note. This is not the AI as a helper you ask questions when you are stuck. The AI is the one on duty. It can look up what this sensor is, ask it questions, and double-check its answers, continuously, without getting bored at 3 am. And that changes your role. You are no longer the person who reads the display. You are the person who designs how the watcher thinks. Every deck in this course starts with this same flip, and then asks what this particular sensor contributes to it.

## Slide 01.2: AI-First: What the AI Must Know About This Sensor

**Slide content:**
- The AI is only as good as what it knows about its senses
- Every sensor carries a sensor card: its ID card, which the AI reads
- This card says: trust me between -10 and +85 degrees
- And: I am honest to about half a degree, no more
- So a 0.3 degree change might mean nothing at all

**Narration:**
Here is the question that decides whether your AI is wise or foolish: what does it know about its own senses? Imagine wearing someone else's glasses without knowing their power. You would see something, and you would trust it far too much. An AI reading a sensor it knows nothing about is in exactly that position. So in this kit, every sensor carries a sensor card: the sensor's ID card, which the AI reads before believing anything. For this thermometer the card says two humble, powerful things. First, trust me between minus 10 and plus 85 degrees; outside that, doubt me. Second, I am honest to about half a degree, and no better. That second line matters daily. When the reading drifts from 25.0 to 25.3, an AI that knows the card shrugs: that could be nothing. An AI without the card would announce a warming trend. Same numbers, completely different wisdom. The difference is what it was told about its senses.

## Slide 01.3: The Agentic Pattern: Predict, Then Measure

**Slide content:**
- Pattern one: guess first, then look
- Like calling a cricket score before checking your phone
- The AI predicts the next reading; the sensor grades it
- Being wrong is the interesting part: something changed
- You design the thinking; the AI does the watching

**Narration:**
Every sensor in this course teaches one habit of agentic thinking, and this is the first: predict, then measure. It is the same fun as guessing a cricket score before you check your phone. You commit to a number first, then the truth arrives and grades you. Our AI works the same way. Before the next reading comes in, it says what it expects: this room should be about 26 degrees at 3 pm. Then the sensor answers. If the AI was right, its picture of the room is good. If it was wrong, that is not failure, that is the interesting part: something changed that it did not know about, a window, a crowd, a faulty sensor. And because the card says half a degree of error is normal, the AI never panics over a 0.3 degree wiggle. Notice the split of roles. You design the thinking: what to predict, and what being wrong should trigger. The AI does the watching, every minute, without getting bored. Now let us meet the little chip this all runs on.

## Slide 01.4: What Is the DS18B20?

**Slide content:**
- A digital thermometer on a chip: senses temperature, reports a number, not a voltage
- Silicon bandgap principle: a transistor junction's voltage shifts predictably with temperature
- On-chip ADC converts that shift to a digital value; no conversion left for the user
- Talks over a single data wire (One-Wire protocol) plus power and ground
- Each chip carries a unique 64-bit serial number burned in at the factory
- In this kit: packaged sensor PSENS-001 on SIM1

**Narration:**
What is the simplest useful question you can ask the physical world? "How warm is it here?" The DS18B20 answers that question in the most convenient form possible: as a finished digital number. Inside the chip, a silicon junction produces a voltage that changes with temperature in a highly predictable way. The chip measures that voltage with its own analog-to-digital converter, applies factory calibration, and hands you a temperature reading in degrees Celsius. You never see a raw voltage, and you never apply a conversion formula, which removes an entire class of student errors before they can happen. Communication happens over a single data line using the One-Wire protocol, so the whole sensor needs only three wires. Every DS18B20 also carries a unique 64-bit serial number, which means several sensors can share the same wire and still be told apart. That one feature, unique addressing on a shared bus, is what makes multi-point temperature mapping possible later in this deck. In the kit, the raw chip lives inside a packaged enclosure with a keyed connector, and it pairs with Sensor Interface Module SIM1, the One-Wire variant. The SIM powers the sensor, runs the bus as master, decodes the bit stream, and broadcasts the temperature as a BLE advertisement that any gateway in range can hear.

## Slide 01.5: What It Does in Practice

**Slide content:**
- One of the most widely deployed temperature sensors in the world
- Cold chain: refrigerators, freezers, cold rooms, refrigerated trucks
- Buildings: homes, hospitals, server rooms, stadiums
- Waterproof variant measures non-corrosive liquids directly
- Where it stops: ±0.5 °C accuracy and +125 °C ceiling; Pt-100 for precision, thermocouple for furnaces
- Selection criteria: range, accuracy, environment, stability, cost

**Narration:**
Where would you actually meet this sensor? Almost everywhere temperature matters but extreme precision does not. The DS18B20 is a workhorse of cold chain monitoring: refrigerators, freezers, cold rooms, and refrigerated trucks all use sensors of exactly this class to prove that food and medicine stayed within safe limits. It appears in homes, hospitals, server rooms, and stadiums, and a waterproof variant of the same chip lets you immerse it in non-corrosive liquids, so aquariums, water heaters, and fermentation tanks are on the list too. Just as important is knowing where it stops. The accuracy is half a degree, and the ceiling is 125 degrees Celsius. If you need a tenth of a degree in an industrial process, the standard answer is the Pt-100, a platinum resistance detector with roughly ±0.15 degree accuracy and a range up to about 600 degrees. If you need to look inside a furnace at over a thousand degrees, you need a thermocouple. Choosing among them is an engineering decision driven by range, accuracy, environment, mechanical constraints, long-term stability, and cost. This kit deliberately gives you the affordable, digital, good-enough sensor, because for climate and building work, half a degree resolved reliably at many points beats a tenth of a degree at one expensive point.

## Slide 01.6: Technical Card

**Slide content:**
- Measurand: temperature; range -55 °C to +125 °C
- Accuracy: ±0.5 °C from -10 °C to +85 °C (wider error outside this band)
- Resolution: 9 to 12 bit, configurable; 0.0625 °C at 12 bit
- Original package: TO-92 three-pin, or waterproof stainless probe variant
- Output: digital, One-Wire protocol; supports parasite power and daisy-chaining
- Packaged sensor dimensions: [PLACEHOLDER]
- Interface/connector details: [PLACEHOLDER: keyed harness, WHAN part number]; SIM1, One-Wire

**Narration:**
Here is the machine-readable heart of this sensor, the same facts that live in its sensor card on the gateway. The measurand is temperature, over a full range of minus 55 to plus 125 degrees Celsius. Accuracy is plus or minus half a degree, but only between minus 10 and plus 85 degrees: outside that band the error widens, and the sensor card carries that accuracy-versus-range function so an agent reasoning about your data knows exactly how much to trust a reading near the edges. So a reported 25.0 means the true value lies between 24.5 and 25.5. Resolution is configurable from 9 to 12 bits; at 12 bits the step size is one sixteenth of a degree, which is finer than the accuracy, a distinction students should internalise: resolution is not accuracy. The raw chip ships in a TO-92 package about the size of a small transistor, and a waterproof stainless-steel probe variant exists for liquids. The output is fully digital over One-Wire, and the bus supports multiple sensors on the same line. The final packaged sensor dimensions and the keyed connector pinout are placeholders here and will be supplied with the production packaging documents. On the kit side, this sensor connects to SIM1, the One-Wire Sensor Interface Module, which acts as bus master and broadcasts each reading over BLE with a sequence counter and a monotonic tick.

## Slide 01.7: Climate Change Applications

**Slide content:**
- Measurement: hyperlocal temperature mapping; urban heat islands street by street
- Long-duration outdoor campaigns on power-bank operation
- Mitigation: quantify HVAC waste; measure delivered cooling against energy burned
- Adaptation: heat-stress monitoring in classrooms, clinics, and dwellings
- Cold chain integrity for food and vaccines, cutting spoilage-driven waste
- Anchor variable: nearly every climate dataset starts with temperature

**Narration:**
Why does a fifty-rupee-class thermometer matter for climate change? Because temperature is the anchor variable of the entire subject, and official weather stations average over kilometres while people live in streets, rooftops, and rooms. With several DS18B20 sensors a student can map an urban heat island directly: measure a shaded park, a paved courtyard, and a tin-roofed room at the same hour and see differences of several degrees that a city-level forecast hides. Because the SIM runs from a power bank, these campaigns can run for days in places with no mains power. On the mitigation side, temperature is how you catch energy waste: a classroom cooled to 19 degrees when 24 would do, or an air conditioner that burns power while barely lowering the room temperature, both show up as measured facts once you log inside and outside temperatures continuously. On the adaptation side, heat stress is already a public-health problem, and continuous measurement in classrooms, clinics, and homes tells you when a space becomes unsafe, not just uncomfortable. And in the cold chain, temperature logging prevents spoilage of food and vaccines, which is climate action twice over: wasted food is wasted embedded energy and methane in landfill. Every other sensor in this kit will, at some point, be interpreted alongside a temperature trace.

## Slide 01.8: Fusion Partners

**Slide content:**
- SCT-013 current sensor: temperature drop versus energy burned equals measured AC efficiency
- Reed switch: explains why cold-chain temperature rose (door open versus compressor fault)
- SCD41: separates thermal comfort from air quality; occupancy context for temperature swings
- Two DS18B20s (daisy-chained): inside/outside pairs, gradients, delivered cooling
- Agent role: MCP tools align the series on tick_ms and reason across them

**Narration:**
A temperature number alone describes; paired with the right second sensor it explains. Pair the DS18B20 with the SCT-013 current clamp and you can ask the question every household wonders about: is my air conditioner actually efficient? The temperature pair, one sensor inside and one outside, tells you the cooling delivered; the current clamp tells you the energy spent; the ratio is a measured efficiency, not a nameplate claim. Pair it with the reed switch on a refrigerator door and a rising temperature stops being a mystery: temperature rising with the door open means someone left it open; rising with the door closed means the compressor or the power has failed, and those two situations demand completely different actions. Pair it with the SCD41 and you can separate "this room is hot" from "this room is hot because it is packed with people," which changes what the HVAC should do. And because One-Wire supports daisy-chaining, two or three DS18B20s on one SIM give you gradients across a single space. The agent is what makes fusion practical for a non-technical student: through the MCP server it discovers both sensors, pulls time-aligned series reconciled on the monotonic tick, and reasons across them. You ask the question in plain language; the model does the joining.

## Slide 01.9: Capstone C1

**Slide content:**
- Question: is this room healthy, and is the HVAC earning its energy bill?
- Sensors: DS18B20 (in/out pair), SCD41, PIR, SCT-013, reed switch
- Contradiction to resolve: cool room, high CO2: comfort is not health
- Decision: a deployable ventilation and setback rule via deploy_rule
- Agent orchestration: capture_experiment, aligned queries, human-approved action

**Narration:**
The capstone that anchors this sensor is capstone C1: is this room healthy, and is the HVAC earning its energy bill? You instrument one real room. A DS18B20 pair measures indoor and outdoor temperature; the SCD41 measures CO2; the PIR watches for motion; the SCT-013 clamps the HVAC supply; a reed switch watches the door or window. The experiment begins with capture_experiment, which records all streams under one dataset handle. The contradiction you must resolve is built in: the room can read a comfortable 24 degrees while CO2 climbs past 1400 ppm, meaning the air conditioner is recirculating stale air. Comfort and health are different claims, and the data will force you to separate them. There is a second contradiction waiting: the energy log will show the compressor running in an empty room, because schedules are not occupancy. The deliverable is a decision, not a chart: a deterministic rule, authored with the model at design time and deployed through deploy_rule with human approval, that sets back cooling when the room empties and flags ventilation when CO2 crosses threshold. The agent orchestrates the analysis: it discovers the sensors, aligns the series on tick_ms, quantifies the waste in measured kilowatt-hours, and drafts the rule. You judge it, correct it, and commit it. That final step, human judgment over model output, is the habit this course exists to build.
