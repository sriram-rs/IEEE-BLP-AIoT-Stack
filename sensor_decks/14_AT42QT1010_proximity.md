# Sensor 14: AT42QT1010 - Proximity / Touch (SIM3, GPIO)

## Slide 14.1: AI-First: The Old Way and the New Way

**Slide content:**
- This sensor answers one tiny question: is something sitting here?
- The old way: a person glances at the counter and just knows
- An AI has no eyes; even obvious facts need a sensor to say them
- The new way: one yes/no bit becomes the AI's sense of presence
- With it, the AI notices every arrival and removal, all day long

**Narration:**
This chip produces the smallest answer in the kit: one bit. Something is sitting here, or it is not. Why would an AI need something so humble? Think about what you do at the canteen counter. You glance, and you instantly know whether a food tray is there. You would not even call that information; it is simply obvious. Now take the AI's position. It has no eyes. However clever it is, it cannot know a single thing about the physical world unless some sensor says it out loud, including facts this small. That is the first habit of AI-first thinking: nothing is obvious to an AI, so you must decide which small facts deserve a sensor of their own. The old way, a person glancing, works only while a person is looking. The new way, this chip reporting its one bit, works all day and every day, and the AI notices every arrival and every removal, each with a timestamp. What that one bit is worth, and what it cannot promise, comes next.

## Slide 14.2: AI-First: What the AI Must Know About This Sensor

**Slide content:**
- An AI is only as good as what it knows about its senses
- The sensor's ID card is refreshingly honest about limits
- It senses within a few centimetres of its pad, never the whole room
- If something sits still for hours, the chip can slowly stop noticing it
- So the AI treats a never-ending "present" with mild suspicion

**Narration:**
Before the AI builds anything on this bit, it reads the sensor's ID card, and this card is refreshingly honest. First limit: reach. The chip senses within roughly two to three centimetres of its metal pad. It can tell you a tray is on the counter; it can never tell you who is in the room. Because the card says so plainly, the AI will never stretch this sensor beyond what it can promise. Second limit, and the more surprising one: the chip constantly re-learns what "nothing here" feels like, so that dust and humidity do not fool it. The side effect is that an object left sitting for many hours can slowly fade into that background, and the chip may stop reporting it even though it is still there. Knowing this, the AI treats a detection that never ends with mild suspicion, and double-checks before drawing conclusions. This is the general lesson of the slide: an AI that knows the limits of its senses can be trusted; one that does not is just guessing confidently. Now for the pattern this one bit makes possible.

## Slide 14.3: The Agentic Pattern: Context Gates Meaning

**Slide content:**
- The pattern: one sensor decides when another sensor's data means anything
- A fuel gauge only matters when there is a car attached
- The heat lamp's temperature only matters while food sits under it
- This chip's yes/no bit switches that meaning on and off
- You choose the gate; the AI applies it, and false alarms disappear

**Narration:**
This sensor's pattern is called Context Gates Meaning, and in one line it says: when data matters can be as important as what the data says. A fuel gauge reading half full is vital information inside your car, and meaningless lying on a workbench. Same gauge, same needle, no car. Now the canteen. A thermometer watches the heat lamp all day and reports faithfully. But those temperatures are a food safety record only while food is actually under the lamp. The rest of the time, they are measurements of hot metal. Which hours matter? This chip answers with its single bit: tray present, or absent. The AI uses that bit as a gate. Before it reasons about temperature at all, it marks each reading as meaningful or irrelevant. Alarms about an empty counter never fire, so the staff never learn to ignore the system. That is the whole trick: one yes or no, switching the meaning of another sensor's data on and off. You choose what gates what; the AI applies the gate every second without fail. Keep the fuel gauge in mind as we now meet the chip that makes the bit.

## Slide 14.4: What It Is

**Slide content:**
- A single-channel capacitive touch and proximity IC from Microchip, using charge-transfer sensing
- The electrode is whatever you attach: a copper pad, a short wire, a foil patch; the designer chooses its size and shape
- The IC repeatedly charges the electrode and measures how much charge it takes; a nearby hand or object adds capacitance and changes the count
- Detects conductive or dielectric objects within approximately 2-3 cm of the electrode
- Output is one GPIO line: HIGH when detected, LOW when not; the same firmware path as the PIR
- Honest scope: this is short-range proximity and touch, not room-scale presence detection

**Narration:**
Every smartphone screen answers a question millions of times a day: is a finger here? The AT42QT1010 is that same capacitive principle reduced to a single chip and a single yes-or-no answer. The method is called charge transfer. The IC connects to an electrode, which is nothing more exotic than a copper pad on a PCB or a few centimetres of wire, and it repeatedly charges that electrode and measures how much charge was needed. Your body, or a food tray, or any object that is conductive or has a reasonable dielectric constant, adds capacitance when it comes near. The chip notices the extra charge and drives its output pin high. That is the whole interface: one digital line, high for detected, low for not. To the SIM, this sensor is indistinguishable from the PIR; the same GPIO event firmware timestamps its edges. Two things make it interesting for a hardware course. First, the sensing element is designed by you: electrode size and shape set the sensing range, so students are designing the sensor, not just wiring it. Second, honesty about scope: this detects things within roughly two to three centimetres. It will never see across a room, and knowing what a sensor cannot do is as valuable as knowing what it can.

## Slide 14.5: What It Does in Practice

**Slide content:**
- Touch controls without moving parts: buttons behind sealed plastic panels, no membrane to wear out
- Object presence: is the tray on the counter, the cup on the coaster, the tool in its slot?
- Fill or content detection through non-metallic walls: liquid behind plastic, grain behind a bin wall
- Human touch detection on handles, rails, and interactive exhibits
- Appliance interfaces: the majority of modern touch-sensitive white goods use this exact principle
- Costs approximately ₹80-150; the electrode itself is nearly free

**Narration:**
What jobs does a two-centimetre yes-or-no sensor actually do? More than you might expect, because an enormous number of real questions are exactly that shape. The first family is touch controls. A mechanical button is a hole in an enclosure: water gets in, springs fatigue, contacts oxidize. A capacitive pad senses straight through a sealed plastic panel, so the enclosure stays waterproof and there is nothing to wear out. Your induction hob, your kettle with touch controls, and most modern appliances use this principle. The second family is object presence. Is the food tray sitting on the heat lamp counter? Is the cup on the docking point? Is the fire extinguisher in its bracket? Mount the electrode under the resting surface and the object's own bulk announces its arrival. The third family is content sensing through walls: because the field passes through non-metallic materials, an electrode on the outside of a plastic tank can tell whether liquid stands behind it at that height, with no hole drilled and no contact with the contents. And the fourth is human touch as an intentional signal: a rail that knows it is being gripped, an exhibit that responds when touched. One chip, one pad, and a surprising range of questions answered.

## Slide 14.6: Technical Card

**Slide content:**
- Measurand: proximity/contact event (binary), objects within approximately 2-3 cm of electrode
- Sensing: self-capacitance, charge-transfer method; sensitivity set by electrode geometry and a sampling capacitor
- Supply: 1.8-5.5 V; approximately 3 µA in low-power mode, sub-millisecond response in fast mode
- Original package: SOT23-6, approximately 3 x 3 mm; electrode is external, designer-defined
- Output: single GPIO, HIGH on detect; recalibrates itself continuously against slow environmental drift
- Packaged sensor dimensions: [PLACEHOLDER]
- Interface/connector details: [PLACEHOLDER: keyed harness part number]
- SIM assignment: SIM3, GPIO event input (identical path to PIR and reed switch)

**Narration:**
The technical card is brief because the chip does one thing. The measurand is a detection event: something conductive or dielectric within roughly two to three centimetres of the electrode, the exact range depending on electrode area and the sampling capacitor you select. The IC itself is a six-pin SOT23 package, about three millimetres on a side; everything the user sees is the electrode, which is external and designed per application. Supply is flexible, 1.8 to 5.5 volts, so the SIM's 3.3 volt rail drives it directly, and consumption in low-power mode is approximately three microamps, which is negligible against the power bank budget. The output is a single GPIO line, high on detection. On SIM3 it rides the identical firmware path as the PIR and the reed switch: debounced edge capture with a monotonic timestamp, broadcast as a BLE event. One behaviour deserves attention because it will show up in your data: the chip continuously recalibrates its baseline. A slow environmental change, humidity rising through the morning, dust settling, gets absorbed silently. But an object left on the pad long enough can be recalibrated into the baseline too, depending on the max on-duration configuration, and the detection eventually clears while the object is still there. The sensor card records this so agents reasoning about a long steady detection know to treat it carefully. Packaged dimensions and connector are placeholders pending production.

## Slide 14.7: Climate Change Applications

**Slide content:**
- Actuation gating: confirm the object is present before spending energy on it; a heat lamp warming an empty counter is pure waste
- Every false alert an agent chases has an energy and attention cost; presence gating cuts false positives at the source
- Sealed touch controls survive outdoor and field deployments: no perforated enclosures, longer equipment life, less e-waste
- Through-wall liquid sensing supports water monitoring with zero contamination path
- Measurement role: usage counting (touches, placements) quantifies how shared resources are actually used

**Narration:**
The climate role of a proximity chip is indirect but real, and it teaches a principle: context gating. Consider the canteen heat lamp. Its job is to keep food warm, but it only has a job when food is present. A lamp warming an empty stainless counter converts electricity into nothing, and a temperature-based food safety monitor that alarms on an empty counter trains staff to ignore alarms. A twenty-rupee electrode under the tray position gives every downstream system the one bit it was missing: is there anything here to care about? Gating actuation and alerting on presence is a pattern that scales far beyond canteens; most automated systems waste energy precisely when their assumptions about occupancy or presence are wrong. The second contribution is durability. Field-deployed climate instrumentation lives outdoors, and every mechanical switch is a hole in the enclosure where water enters. Capacitive controls behind sealed plastic mean IP-rated boxes that stay rated, equipment that lasts longer, and less electronic waste. Third, through-wall sensing lets you monitor water in tanks and channels without touching the water, no contamination path, no corrosion. And as a measurement instrument, simple placement and touch counting quantifies how shared resources, water points, tool cribs, charging docks, actually get used, which is the data that justifies providing more of them.

## Slide 14.8: Fusion Partners

**Slide content:**
- DS18B20: tray-present AND temperature is the meaningful HACCP record; temperature of an empty counter is noise
- JSN-SR04T: queue depth plus tray presence separates people waiting from food being served
- PIR: person versus object disambiguation; PIR sees the human, the pad sees the tray
- Reed switch: same GPIO family; together they give door, lid, and placement events on one SIM3
- Agent inference via MCP: validate_reading gates temperature alerts on presence; capture_experiment aligns service events with queue dynamics

**Narration:**
This sensor's value multiplies fastest through fusion, because a single presence bit is exactly the missing context other sensors need. Start with the DS18B20 on the heat lamp counter. A temperature log of that counter is only a food safety record when food is on it; the rest of the time it is a log of hot metal. Fuse the two and the agent produces the record an auditor actually wants: while food was present, from 12:05 to 14:20, the temperature stayed above the safe holding threshold, or it did not, and here are the minutes it spent below. The presence bit converts data into evidence. Pair it with the JSN-SR04T watching the queue and the canteen picture completes: the ultrasonic sensor measures how many people are waiting, the pad answers whether food is actually being served. A long queue with no tray on the counter is a service problem, not a demand problem, and no single sensor can make that distinction. With the PIR, the fusion resolves identity: PIR fires on the person reaching over the counter, the pad fires on the tray itself, and the timing between the two events separates a person browsing from a tray landing. In the MCP architecture, the validate_reading tool consults the presence stream before honouring a temperature alarm, and capture_experiment records aligned service-event datasets for the capstone analysis.

## Slide 14.9: Capstone C4: Is the Canteen Safe, and How Long Is the Queue?

**Slide content:**
- Question: is food held at safe temperatures whenever food is actually present, and does service keep up with the queue?
- Sensors: DS18B20 (holding temperature), AT42QT1010 (tray presence), reed (cold-store door), JSN-SR04T (queue depth), SPL (crowd noise)
- The AT42QT1010's role: gate every hot-side alert and every HACCP log entry on tray presence
- Contradiction to resolve: temperature alarms with no food present, and quiet queues that are long versus noisy crowds that are short
- Agents produce the daily food safety report and the service-timing analysis from one aligned dataset
- Decision at the end: a staffing and holding-temperature policy backed by measured evidence

**Narration:**
The canteen capstone runs two investigations on one deployment: a food safety question and a service quality question, and the proximity pad is the hinge between them. On the safety side, the DS18B20 logs holding temperature at the heat lamp and the reed switch logs every cold-store door event. The AT42QT1010 sits under the tray position and contributes the gating bit: log and alarm only when food is present. Without it, the first week of data drowns in false alarms from an empty counter, and students experience first-hand why alarm fatigue is a safety failure mode, not an annoyance. On the service side, the ultrasonic sensor measures queue depth at the serving line while the sound sensor tracks crowd noise, and the tray pad marks actual service events. The contradiction to resolve is a genuine operational one: the queue is long but the counter shows continuous tray turnover, meaning demand is high and service is fine, versus the queue is long and trays are absent, meaning the kitchen is behind. Those need different fixes, and the agent must distinguish them from the aligned timeline. The final deliverable is a decision memo to the canteen operator: measured holding-temperature compliance while food was present, the peak service windows, and a staffing recommendation defended with data an auditor could re-derive from the raw streams.
