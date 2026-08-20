# Sensor 10: Reed Switch - Door/Window Contact State (SIM3, GPIO)

## Slide 10.1: AI-First: The Old Way and the New Way

**Slide content:**
- Old way: the warm fridge is discovered at breakfast, cause unknown
- New way: an AI watches the door and the temperature together, all night
- It does not just report a problem; it explains which problem
- Door open and warming: carelessness. Door closed and warming: failure
- The right explanation decides whether the food is saved or thrown away

**Narration:**
Picture a canteen refrigerator at two in the morning. The temperature inside creeps from 3 degrees to 8. The old way, nobody knows until breakfast, and then comes the hard question: did someone leave the door open, or is the fridge dying? The answer decides everything. If it was the door, close it and check the food. If it was the compressor, the fridge is failing and the food must move now. A thermometer alone cannot tell you which story is true. The new way pairs the thermometer with the simplest sensor in our kit: a magnet and a tiny switch on the door frame that answer one question, open or closed. Now the AI is like a night watchman who saw the whole thing happen. It does not just report that the fridge is warm; it explains why, and the explanation picks the action. That is the heart of the new way: not more numbers, but enough context to turn a number into a story you can act on.

## Slide 10.2: AI-First: What the AI Must Know About This Sensor

**Slide content:**
- The sensor's ID card says: two states, open and closed, with exact times
- This sensor does not stream numbers; it speaks only when something changes
- Its one known lie: a fallen magnet reads "open" forever
- So silence has two meanings: nothing happened, or the sensor cannot speak
- The AI checks the sensor's heartbeat, so silence can be trusted

**Narration:**
What must the AI know before trusting a sensor this simple? The sensor's ID card is the shortest in the kit. It says: I report two states, open and closed, each stamped with the exact time. I do not stream numbers all day; I speak only when the world changes. That silence is efficient, but it hides a trap. Think of a letterbox. An empty letterbox usually means no mail, but it could also mean the slot is jammed. Same here: a door that reports nothing for a week is either a door nobody opened, or a magnet that fell off, and a fallen magnet is this sensor's one known lie: it reads open, forever. The card warns the AI about exactly this. So the AI does something a casual observer never would: it regularly checks that the sensor itself is alive, its heartbeat, separately from what the sensor says. Only then is silence good news. One tiny sensor, and already the deepest lesson in trusting instruments: know how your sensor fails, or its silence will fool you.

## Slide 10.3: The Agentic Pattern: Events, Not Samples

**Slide content:**
- Pattern in one line: some sensors speak only when something happens
- This one is a doorbell, not a diary
- One ring, "door opened at 2 am", starts an AI investigation
- The AI checks temperature, checks motion, and writes down the story
- You design the thinking; the AI does the watching

**Narration:**
The pattern this deck adds: events, not samples. Most sensors are like a diary that writes "nothing new" every five seconds. This sensor is a doorbell. It stays quiet until the world changes, then rings once, with the time attached: door opened, 02:14 am. For an AI, that ring is a starting gun. The moment the cold-room door opens in the middle of the night, the AI begins a small investigation: how is the temperature behaving, did the corridor motion sensor fire, how long did the door stay open? By morning there is a story with times and evidence, not a mystery and a puddle. Compare that with checking the door hundreds of times a day just in case; the doorbell way never misses the moment and wastes no effort. Your part is deciding, in advance, what a ring should make the AI do. The AI's part is being awake at 2 am to do it. You design the thinking; the AI does the watching. Now let us meet the ninety-year-old invention behind the doorbell.

## Slide 10.4: What It Is

**Slide content:**
- Two ferromagnetic contacts sealed in a glass tube; a nearby magnet pulls them together
- Two-part install: magnet on the moving part (door), switch on the frame
- Output: a single bit, circuit closed or open; no power needed to sense
- The simplest sensor in the kit, and the only one that measures state, not a quantity
- Hermetically sealed: no wear from dust, humidity, or corrosion; lifetimes in the millions of operations
- Invented 1936 at Bell Labs; still the standard door sensor in every alarm system

**Narration:**
Every sensor so far has measured a quantity: degrees, ppm, decibels, metres. This one measures a fact. Is the door open or closed? Inside a reed switch are two thin blades of ferromagnetic metal, sealed in a small glass tube filled with inert gas. Bring a magnet close and the blades magnetise, attract, and touch: the circuit closes. Take the magnet away and they spring apart: the circuit opens. The installation is two parts: the magnet goes on the thing that moves, the door or window leaf, and the switch goes on the frame. When the door is shut the magnet sits next to the switch and holds it closed; open the door a few centimetres and the contact releases. That is the entire sensing principle, and its simplicity is its strength. The contacts are hermetically sealed, so dust, humidity, and corrosive air never reach them, and they survive millions of operations. The switch consumes no power to hold its state; the SIM merely checks whether a circuit is complete. The design dates to Bell Labs in 1936 and remains the standard door sensor in every burglar alarm on earth, which tells you something: when a sensor is this cheap, this reliable, and this unambiguous, ninety years of engineering finds no reason to replace it.

## Slide 10.5: What It Does in Practice

**Slide content:**
- Cold chain: fridge and freezer door events, the missing context for every temperature alarm
- Disambiguation: temperature rising + door open = close the door; temperature rising + door closed = compressor fault, move the food
- HACCP food safety: above 5 °C for over 4 hours means discard; the event log proves it either way
- Security: after-hours access logs, intrusion sequences, cabinet and rack tamper
- Lab safety: fume cupboard sash position, autoclave latch, chemical store access
- Building state: window-open detection for HVAC logic

**Narration:**
The reed switch's day job is context. Consider a canteen refrigerator with a temperature sensor inside. At 11:47 the temperature starts climbing. What should the staff do? The honest answer is: it depends on why, and temperature alone cannot tell you. If the door is open, someone left it ajar; close it and the problem is solved. If the door is closed, the compressor or the power has failed, and the food needs moving now. Same temperature trace, opposite actions, and the twenty-rupee reed switch is what disambiguates them. Food safety regulation makes this concrete: under FSSAI's HACCP requirements, food held above five degrees for more than four hours is a discard event, and the combined door-plus-temperature log documents exactly when the door opened, how long it stayed open, and what peak temperature the load reached. The most dangerous failure it catches is the door that fails to latch overnight: a morning temperature check might read seven degrees and tempt someone to judge the food acceptable, but the log shows eight hours above threshold, and the decision becomes unambiguous. Beyond the cold chain, the same bit secures things: after-hours door events at equipment rooms, rack and cabinet tamper, fume cupboard sashes left up, chemical stores opened outside authorised windows. One bit, correctly timestamped, is worth a paragraph of explanation.

## Slide 10.6: Technical Card

**Slide content:**
- Measurand: binary contact state (magnet present/absent), i.e. door or window open/closed
- Actuation distance: approximately 10-20 mm gap, magnet dependent; hysteresis prevents chatter
- Accuracy: state detection is essentially error-free; event timing resolved to milliseconds by SIM3 interrupts
- Raw device: glass-encapsulated reed contact in plastic housing, paired magnet block
- Output: dry contact, wired as GPIO with internal pull-up; closed = low, open = high
- Packaged sensor dimensions: [PLACEHOLDER]
- Interface and connector details: [PLACEHOLDER: keyed harness part number]
- SIM assignment: SIM3 (GPIO), same debounced edge-capture path as the PIR

**Narration:**
The technical card is short, which is the point. The measurand is a binary state: magnet near, magnet far, which we install to mean door closed, door open. The switch actuates when the magnet comes within roughly ten to twenty millimetres, depending on the magnet supplied, and there is deliberate hysteresis between the closing and opening distances so a door vibrating in its frame does not generate a stream of false events. As a sensor there is essentially no accuracy question: the state is either detected or it is not, and what we actually care about is timing, which SIM3 provides by timestamping each edge with its GPIO interrupt system to millisecond precision, the same debounced edge-capture path the PIR motion sensor uses. Electrically the switch is a dry contact: it carries no electronics, no supply rail, nothing to fail. The SIM wires it between an input pin and ground with an internal pull-up resistor, so a closed door reads low and an open door reads high; firmware debounces the transition and broadcasts the new state, with the event carried in the standard BLE frame alongside the sequence counter and tick. Because there is no analog chain, no calibration, and no drift, this is the sensor whose data you never have to doubt, a property the validation labs will exploit. Packaged dimensions and the keyed connector remain placeholders for the production hardware.

## Slide 10.7: Climate Change Applications

**Slide content:**
- The costliest common waste: air conditioning fighting an open window, invisible to every other sensor
- Envelope-open detection marks CO2 and temperature data as invalid for control, preventing wrong HVAC decisions
- Natural ventilation logic: mild outdoor air + window open = mechanical ventilation off, free cooling
- Cold chain efficiency: door-open minutes are compressor kilowatt-hours; behaviour change becomes measurable
- Root-cause attribution keeps the whole sensing model honest, and honest models are what save energy

**Narration:**
Why does a door sensor belong in a climate course? Because the single most common HVAC energy waste in institutional buildings is a machine fighting an open window, and no other sensor in this kit can see it. Picture a classroom with the air conditioner running and a window open. The AC works continuously against an infinite supply of warm outdoor air. Worse, every clever sensing model we have built gets fooled: CO2 stays low because the room is naturally ventilated, so the occupancy model may read the room as empty; the temperature holds roughly steady, so nothing looks wrong. The system is haemorrhaging energy while every dashboard shows green. A reed switch on the window ends the deception with one bit: envelope open. The gateway then marks the CO2 and temperature streams as invalid for control decisions, the agent alerts rather than adjusts, and the simultaneous heating-and-cooling event gets logged and quantified, evidence that eventually justifies a window-closing policy or an interlock. The same logic runs in reverse for mitigation: when outdoor air is mild and windows are open, mechanical ventilation can switch off entirely, because nature is providing it free. And in the cold chain, door-open minutes translate directly into compressor kilowatt-hours, so staff behaviour, propping the walk-in door during deliveries for instance, becomes a measured, improvable number rather than a nagging suspicion.

## Slide 10.8: Fusion Partners

**Slide content:**
- DS18B20: door state + temperature = cold chain root-cause diagnosis (the four-quadrant table)
- SCD41: window state marks CO2 occupancy inference valid or invalid; kills the ventilation confound
- SCT-013: window open + compressor current flowing = simultaneous heat-and-cool waste, logged and costed
- PIR: door_open then PIR zone 1 then PIR zone 2 = three-stage intrusion narrative; door with no PIR = door ajar
- Agent role: event-sequence reasoning over timestamped bits, via `query_timeseries` and `annotate`

**Narration:**
The reed switch never works alone; its whole value is what it does to other sensors' data. With the DS18B20 it forms the four-quadrant cold chain diagnosis: temperature rising with the door open means close the door; rising with the door closed means compressor or power failure; stable with the door open means a brief, harmless access; stable and closed means all is well. Two sensors, four states, four different actions. With the SCD41 it acts as a validity gate: CO2-based occupancy estimation silently assumes a closed room, so the window switch tells the agent when that assumption holds; readings taken with the envelope open are flagged in the store, and the occupancy model abstains rather than guesses. With the SCT-013 current clamp it catches the most expensive quadrant of all: window open while the compressor draws eight amps is simultaneous heating and cooling, and the pairing timestamps, quantifies, and costs every such event. With the PIR it builds security narratives: door opens, then motion in zone one, then zone two, is an entry, and the ordered timestamps tell the story; a door event with no motion following is a door left ajar, a different threat needing a different response. Notice what the agent is doing in every pairing: not arithmetic on continuous signals but reasoning over sequences of timestamped facts. That is exactly what language models are good at, which makes this humble sensor the most AI-native device in the kit.

## Slide 10.9: Capstone C5: Is the Restricted Zone Secure Against More Than One Threat?

**Slide content:**
- Question: can one room defend itself against intrusion, tamper, flood, and equipment failure at once?
- Sensors: reed (door), PIR (motion zones), VEML7700 (enclosure tamper), SCT-013 (equipment load), water level trace (flood)
- Contradiction to resolve: single-sensor alerts are noisy; demanding multi-sensor agreement can miss real, single-channel events
- Decision: a tiered alert policy, which sequences page a human at 2 a.m. and which wait for morning
- Agents: watchdog reconstructs event narratives from timestamps and drafts the incident report

**Narration:**
The final project turns a server room into something that can defend itself, and the reed switch is its narrator. Five threat channels run simultaneously: the reed switch on the door, PIR sensors covering two interior zones, a VEML7700 sealed inside an equipment cabinet where any light means the cabinet was opened, an SCT-013 clamp on the equipment supply, and the bare-trace water sensor under the rack. The design tension the students must resolve is real: alert on any single sensor and the system cries wolf, a corridor draught trips the PIR and someone stops trusting the pages; demand agreement from multiple sensors and you go blind to genuine single-channel events, because a slow water leak touches only the trace, and a door left ajar touches only the reed. The resolution is sequence reasoning rather than voting. Door open, then zone-one motion, then zone-two motion, inside twenty seconds: that is an entry, and after hours it pages immediately. Door open with no motion following: door ajar, a security defect but not an active intrusion, so it waits for morning. Cabinet light spike with no door event at all: tamper by someone who was already inside, the most serious narrative of all. The watchdog agent reconstructs these narratives from the timestamped event streams through the MCP tools, drafts the incident report with its evidence chain, and the students' deliverable is the tiered alert policy itself, defended threat by threat.
