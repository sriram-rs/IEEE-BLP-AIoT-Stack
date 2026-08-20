# Sensor 03: PIR - Motion (SIM3, GPIO)

## Slide 03.1: AI-First: The Old Way and the New Way

**Slide content:**
- The old way: flash means someone is there, quiet means nobody
- The new way: an AI interprets what the sensor saw, and did not see
- Everyday failure: you sit still reading, and the lights go off
- The AI treats quiet as a question, not an answer
- You decide what the AI may conclude from silence

**Narration:**
Picture a library. You are deep in a book, perfectly still, and the lights go off. The motion sensor stopped seeing you, and a dumb rule decided the room was empty. Everyone has met this failure; it is the old way in action: sensor flashes, lights on; sensor quiet, lights off; no thinking in between. The new way places an AI between the sensor and the switch. The sensor still only reports motion or no motion; it is a simple device and always will be. The intelligence sits behind it. The AI treats every quiet stretch as a question: does this quiet mean an empty room, or a still person? It considers how long the quiet has lasted, what else it knows about the room, and how costly a wrong guess would be. An exam hall going dark is a very different mistake from a corridor light staying on. Deciding what the AI may conclude from silence, and how carefully it must check first, is your design work. That is what this deck trains.

## Slide 03.2: AI-First: What the AI Must Know About This Sensor

**Slide content:**
- The sensor's ID card carries a warning the AI must read
- Still people turn invisible to it in about 30 seconds
- So quiet has three meanings: empty room, still person, dead sensor
- Each radio message is numbered, so a dead sensor gives itself away
- No motion never simply equals no people

**Narration:**
What must the AI know about this sensor before trusting it? One warning above all, and it is written on the sensor card, the sensor's ID card that the AI reads: anyone who stops moving for about thirty seconds becomes invisible. This sensor detects change in body heat, not presence itself. A sleeping baby, a reading student, a lecturer standing still at the board: all invisible. Once the AI knows that, it understands that quiet has three possible meanings, and they call for three different responses. The room may truly be empty. A person may be sitting still. Or the sensor itself may be dead: flat battery, radio out of range. The kit helps with the third case in a simple way: every radio message from the sensor carries a running number, like numbered pages in a notebook. If the numbers stop arriving, the AI knows it lost the sensor, not the people. The middle case, the still person, cannot be solved by this sensor at all. Knowing what your senses cannot tell you is as valuable as knowing what they can, and it sets up the pattern this deck teaches.

## Slide 03.3: The Agentic Pattern: Absence of Evidence

**Slide content:**
- The pattern: no news is not good news, it is just no news
- A silent baby monitor: asleep baby, or dead battery?
- The AI stays unsure and asks a second sensor
- CO2 falling and sound fading: now "empty" is believable
- You decide what silence may mean; the AI checks before acting

**Narration:**
The pattern here is called Absence of Evidence, short for an old saying: absence of evidence is not evidence of absence. In plain words: no news is not good news, no news is just no news. Think of a baby monitor that has gone quiet. Is the baby asleep, or is the monitor's battery dead? You would never conclude anything from the silence alone; you would peek into the room, or check the monitor's light. Our AI is built to do the same. When the motion sensor goes quiet, the AI stays unsure. It asks a second sensor with different senses: is the CO2 level falling, the way it does when people leave a room? Has the sound level dropped to the building's background hum? Only when the witnesses agree does "empty" become believable, and only then do the lights go off or the cooling wind down. The roles split cleanly again: you decide what silence may mean and what must be checked before acting; the AI does the checking, every time, without shortcuts. Now let us meet the sensor whose silence we have been discussing.

## Slide 03.4: What Is a PIR Sensor?

**Slide content:**
- Passive Infrared: detects the heat humans radiate, emits nothing itself
- Pyroelectric element responds to change in infrared, not to steady heat
- Fresnel lens divides the view into zones; a warm body crossing zones creates the signal
- Output is a single digital line: motion or no motion
- Detection field: approximately 100 degree cone, 3 to 7 m range
- In this kit: SIM3, GPIO interface, interrupt-timestamped events

**Narration:**
How does an automatic light know you walked in? Almost always, through a PIR sensor, and the P matters: it stands for passive. The sensor transmits nothing. It simply watches the infrared heat that every human body radiates continuously. At its heart is a pyroelectric element, a crystal that generates a tiny charge when the amount of infrared falling on it changes. The key word is changes: a warm room at steady temperature produces no signal at all, but a warm body moving across the field of view produces a clear one. The white plastic dome on top is a Fresnel lens, and it is doing real optical work: it slices the scene into many wedge-shaped zones, so that a person walking across the room passes from zone to zone and creates exactly the fluctuating infrared pattern the crystal detects best. Analog circuitry inside the module amplifies that flicker and compares it against a threshold, and what comes out is the simplest possible sensor output: one digital line that is high when motion is detected and low otherwise. The coverage is a cone of roughly 100 degrees reaching three to seven metres. In this kit the PIR connects to SIM3, the GPIO Sensor Interface Module, which timestamps every edge with an interrupt and broadcasts occupancy events over BLE.

## Slide 03.5: What It Does in Practice

**Slide content:**
- The default occupancy sensor of the built world: lights, doors, alarms
- Corridor and pathway lighting, automatic doors, washroom fixtures
- Security systems: cheap, low-power, no privacy concerns (no camera, no audio)
- Wildlife monitoring: camera traps trigger on PIR
- The honest limitation: a person sitting still vanishes after roughly 30 seconds
- False triggers near heat sources and on very hot days

**Narration:**
The PIR is the default occupancy sensor of the built world. Corridor lights that switch on as you approach, automatic doors, washroom taps and flushes, burglar alarms, and the camera traps that photograph tigers in forest reserves: all PIR. Three properties explain that dominance. It is cheap, it sips microamps of power, and it raises no privacy concerns, because it captures no image and no audio, only the fact that something warm moved. For public institutions, that last property is often the deciding one. Now the honest part, and in this course we lead with limitations rather than hiding them: the PIR detects change in heat, so a person who sits still effectively disappears within about thirty seconds. A library full of motionless readers looks empty to a PIR. The reverse failure also exists: anything that changes the infrared scene can masquerade as a person, a curtain flapping over a sunny window, a hot air vent cycling, a pet. And on very hot days, when skin temperature and air temperature converge, contrast drops and range shortens. None of this makes the PIR a bad sensor. It makes it a fast, cheap motion channel that must be fused with slower, steadier evidence, and that fusion story is exactly why this kit carries the SCD41, the SPL sensor, and the ultrasonic ranger alongside it.

## Slide 03.6: Technical Card

**Slide content:**
- Measurand: human/animal motion (binary event), not presence, not count
- Field: approximately 100 degree cone; range approximately 3-7 m
- Supply per module datasheet: 5-20 V (module regulates internally); output high approximately 3.3 V
- Adjustable: sensitivity and hold time on typical modules
- Original part: pyroelectric element plus Fresnel lens on a small carrier board
- Packaged sensor dimensions: [PLACEHOLDER]; connector: [PLACEHOLDER]
- SIM3, GPIO; edge-interrupt timestamping; multiple units cascadable on one bus line

**Narration:**
Read this card carefully, because its most important line is what the sensor does not measure. The measurand is motion events, binary, one or zero. It is not presence, and it is not a head count; treating a PIR as a presence sensor is the single most common misuse, and the sensor card on the gateway states the roughly thirty-second stationary blind spot explicitly so that an agent reasoning over the data inherits that caution automatically. The field of view is a cone of about 100 degrees with a range of three to seven metres, adjustable on most modules along with the output hold time. The module accepts a supply of five to twenty volts and regulates internally, and its output pin swings to about 3.3 volts on detection, directly compatible with the ESP32 on SIM3. Inside the packaged enclosure sits a standard pyroelectric element behind its Fresnel lens on a small carrier board. The packaged dimensions and the keyed connector pinout are placeholders pending production documents. Two integration details matter. First, SIM3 timestamps each rising and falling edge with a hardware interrupt, so the gateway receives events with clean timing for sequence analysis. Second, the packaged design allows several PIR units to be cascaded onto one line, trading spatial resolution for coverage: you learn that something moved in a large area, but not which sensor saw it.

## Slide 03.7: Climate Change Applications

**Slide content:**
- Occupancy-driven energy: lighting and HVAC that follow people, not schedules
- Buildings consume roughly a third of global energy; occupancy sensing is the cheapest lever
- Conserving water: presence-gated fixtures in public washrooms
- Wildlife and biodiversity monitoring under habitat shift
- The fast trigger in demand-controlled systems; other sensors confirm

**Narration:**
Why does a motion detector belong in a climate course? Because buildings consume roughly a third of the world's energy, and a large slice of that is spent lighting and cooling rooms with nobody in them. The cheapest, fastest-payback intervention in the entire efficiency toolkit is making energy follow people, and the PIR is the sensor that makes that possible at scale: corridor lighting that activates on approach, HVAC that sets back when a zone goes quiet, escalators that idle until someone arrives. Every one of those saved kilowatt-hours is generation that never happened. The same logic conserves water: presence-gated taps and flushes in public washrooms cut consumption without asking anyone to change behaviour, which is precisely why they work. There is also a field-science role: PIR-triggered camera traps are a standard instrument of biodiversity monitoring, and as habitats shift under warming, those triggers are how researchers track animal movement and migration without a human observer disturbing the scene. In this kit's architecture the PIR plays a specific position: it is the fast trigger. It responds instantly when someone enters, which slower evidence like CO2 cannot do, and then hands off to the slower sensors for confirmation that people are still there. Fast but forgetful, paired with slow but sure: that is the design pattern, and it recurs throughout this course.

## Slide 03.8: Fusion Partners

**Slide content:**
- SCD41: CO2 confirms stationary occupants the PIR forgets; PIR gives the speed CO2 lacks
- SPL: sound distinguishes a silent empty room from a silent full one, instantly
- JSN-SR04T: seat-level occupancy for people sitting motionless
- VEML7700: motion AND darkness is the correct lighting rule; motion alone wastes energy
- Reed switch: door event before motion event builds an entry narrative
- Agent role: fuses all channels into an occupancy state machine via MCP queries

**Narration:**
Every fusion pairing for the PIR exists to cover one of its two failure modes: it forgets stationary people, and it can be fooled by heat that is not a person. The SCD41 covers the first: humans exhale CO2 whether or not they move, so rising CO2 confirms that the people the PIR stopped seeing are still there, while the PIR provides the instant response that CO2, with its minutes-long lag, cannot. The SPL sensor covers the same gap at zero latency: a room can be silent and full during an exam, and the combination of no motion, quiet sound, and elevated CO2 identifies exactly that state, which no single sensor can name. The ultrasonic ranger takes it to seat level: mounted overhead, it reads the distance to a chair and knows someone is in it, motion or not. The VEML7700 pairing fixes a different mistake, the lighting rule: motion alone should never switch on a light; motion AND insufficient daylight should, and that one added condition is a measurable energy saving. The reed switch adds narrative order: door opens, then motion begins, tells a different story than motion with no door event, which might be a curtain or a heat vent. The agent assembles all of this through timeseries queries into a single occupancy state machine, and then, in the fault-injection labs, has to catch the day the instructor warms the PIR with a heat source.

## Slide 03.9: Capstone C2

**Slide content:**
- Question: should the lights be on at all?
- Sensors: PIR, VEML7700, SCT-013 on the lighting circuit
- Contradiction to resolve: motion in a fully daylit corridor; lights on, nobody there
- Baseline week versus rule week: measured kWh, not estimated savings
- Decision: deploy the two-condition lighting rule via deploy_rule, edge loop, no LLM at runtime

**Narration:**
Capstone C2 asks the smallest question in the catalog, and answers it with unusual rigor: should the lights be on at all? Instrument one corridor. The PIR provides the motion channel, the VEML7700 measures how much daylight the corridor already has, and the SCT-013 clamps the lighting circuit so that every claim about energy ends in measured kilowatt-hours rather than estimates. Run week one as baseline: lights on their existing schedule or switch, all three sensors logging. The data will hand you both contradictions this project is built around: hours where motion triggered lighting in a corridor already at 600 lux from its windows, and hours where lights burned with no motion at all. Then, with the model as a design-time assistant, author the correct rule: lights on when motion is detected AND lux is below threshold; off after a no-motion timeout OR when daylight suffices. That rule is deliberately deterministic. It deploys to the edge device through deploy_rule with human approval, and it runs with no model in the path, because a corridor light must work the day the internet does not. Run week two under the rule. The deliverable is the difference between the two weeks in measured kilowatt-hours, an honest delivery-ratio account of any BLE packet loss from the seq counters, and a one-page recommendation. The agent's role is analysis and drafting; the judgment, and the deployment decision, stay with you.
