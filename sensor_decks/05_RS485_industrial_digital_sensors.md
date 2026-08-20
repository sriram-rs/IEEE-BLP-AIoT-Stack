# Sensor 05: RS485 Industrial Digital Sensors - Multi-Parameter Industrial Data (SIM5, RS485 / Modbus RTU)

## Slide 05.1: AI-First: The Old Way and the New Way

**Slide content:**
- The old way: a person walks to the meter, reads it, decides
- Meters get checked once a day, and problems wait until then
- The new way: an AI watches this sensor for you, all day
- It notices trouble in seconds, not at tomorrow's inspection round
- Your role changes: from meter reader to designer of the watcher

**Narration:**
Start with a simple change of picture. The old way: somewhere on campus there is a pump room with a meter on the wall, and once a day a person walks in, reads the number, writes it in a register, and leaves. If something went wrong an hour after that visit, nobody knows until tomorrow. That is like checking your letterbox once a day and hoping nothing urgent arrived. The new way: an AI watches that same number for you, all day, every day, and speaks up within seconds when something matters. Nothing about the sensor changed. What changed is who is doing the perceiving. In this course, the sensor is no longer something you read. It is something an AI reads, continuously, on your behalf. And that changes your role too. You are not the meter reader anymore. You are the person who designs the watcher: what it looks at, what it should worry about, and who it should tell. Keep that picture as we look at what the AI needs to do this job well.

## Slide 05.2: AI-First: What the AI Must Know About This Sensor

**Slide content:**
- An AI is only as good as what it knows about its senses
- Industrial sensors answer through numbered boxes, like a printed form
- Box 42 always holds the voltage; divide by one hundred
- The sensor's ID card gives the AI that form, so it never guesses
- The card also lists warning signs, like a value stuck for hours

**Narration:**
Here is a rule that applies to every AI system you will ever build: the AI is only as good as what it knows about its own senses. So what must it know about this one? Industrial sensors like ours answer through numbered boxes. Box 42 always holds the voltage, and you divide it by one hundred to get volts. It is like a bank form: every box has one printed meaning, fixed for everyone. A scribbled note can be misread; a form cannot. Our platform hands the AI the sensor's ID card, a small file that lists those boxes, the units, the conversion for each number, and what can go wrong. That last part matters just as much. The card tells the AI what a healthy answer looks like, and what a suspicious one looks like: a value frozen at exactly the same number for six hours, or a sensor that stops answering altogether. With the card, the AI can look up what this sensor is, ask it questions, and double-check its answers. Without the card, even the smartest AI is guessing. With it, it never has to.

## Slide 05.3: The Agentic Pattern: Contracts All the Way Down

**Slide content:**
- The pattern in one line: machines cooperate through written agreements
- This sensor's agreement is a short table called a register map
- Every box in the table has one fixed, printed meaning
- The AI reads the table; it never fills in guesses
- You design the agreement; the AI does the reading and watching

**Narration:**
Every sensor in this course teaches one thinking pattern, and this deck's pattern is called Contracts All the Way Down. It means: machines cooperate through written agreements, and so should AIs. Think of the bank form again. When every box has one printed meaning, anyone, human or machine, can fill it or read it without a mistake. This sensor ships with exactly such a form. It is called a register map: a short table saying which box holds moisture, which holds temperature, and how to convert each number. When we ask an AI to write the code that reads this sensor, we give it the table. The AI writes correct code on the first try, because there is nothing to guess. And if the table is missing, a well-built AI stops and asks; it does not invent. That is the habit to carry into every AI project you will ever run: give the machine an agreement, not a puzzle. You design the agreement; the AI does the reading and the watching. Hold onto that as we now meet the sensor family itself.

## Slide 05.4: What It Is

**Slide content:**
- Not one sensor: a whole family of industrial instruments that speak a shared digital language
- RS485 is the electrical layer: two wires, differential signalling, robust over hundreds of metres
- Modbus RTU is the data layer: a request-response protocol from 1979, still the industrial default
- Each device holds its measurements in numbered registers; the master reads them on demand
- In this kit: SIM5 is the Modbus master, the sensor is the slave
- Worked examples: an RS485 soil probe and an RS485 energy meter

**Narration:**
Every sensor we have met so far speaks its own private dialect: One-Wire for the temperature sensor, I2C for the gas sensor, a bare voltage for the analog family. Industry solved this differently. Factories needed hundreds of instruments, spread across large sites, all readable by one controller, and they needed the wiring to survive electrical noise from motors and welders. The answer, standardised decades ago and still dominant today, is RS485 carrying the Modbus RTU protocol. RS485 is the electrical part: two wires carrying a differential signal, meaning the receiver looks at the difference between the wires rather than either wire alone. Noise hits both wires equally, so the difference survives. That single trick lets the same cable run for hundreds of metres through an electrically hostile plant. Modbus is the conversation on top: every device has an address, and inside every device the measurements live in numbered registers, like pigeonholes. A master device asks, "device 5, give me registers 10 and 11," and the slave answers with the bytes. Nothing happens until the master asks. In our kit, the Sensor Interface Module SIM5 plays the master, and whichever industrial instrument you connect plays the slave. Learn this pattern once and you can read thousands of real industrial products.

## Slide 05.5: What It Does in Practice

**Slide content:**
- One interface, many instruments: soil probes, energy meters, flow meters, weather stations, VFDs
- Multi-drop: up to 32 devices on one twisted pair, each with its own address
- Polled operation: the master schedules reads, so bus traffic is deterministic
- Kit example 1: soil probe reporting moisture and soil temperature from buried steel electrodes
- Kit example 2: panel energy meter reporting voltage, current, power, energy, power factor
- The skill transfers directly to building management and factory automation systems

**Narration:**
What do you actually meet on an RS485 bus in the real world? Almost everything industrial. Soil probes for agriculture, panel-mounted energy meters, water flow meters, complete weather stations, variable frequency drives running pumps and fans, level transmitters on tanks. The reason is multi-drop wiring: a single twisted pair can carry up to 32 devices, each answering to its own address, so a building management system reads a whole floor of meters over one cable. Our kit gives you two working examples. The first is the soil probe from the Rev5 kit: stainless steel rods buried in the ground, with conditioning electronics that measure conductivity between the rods and store moisture and soil temperature in registers. The second is the energy meter: it sits in line with an appliance, continuously measuring voltage and current, computing active power, reactive power, apparent power, power factor, and accumulated energy, all held in registers waiting to be read. Notice what both have in common: the hard measurement work happens inside the instrument, and the interface only delivers finished numbers. The practical skill you take away is reading a register map from a datasheet, because that is exactly how a commissioning engineer brings a new instrument online anywhere in the world.

## Slide 05.6: Technical Card

**Slide content:**
- Electrical: RS485 differential pair (A/B), half-duplex, typical 9600 baud 8N1 in this kit
- Protocol: Modbus RTU, master-slave, CRC-16 checked frames
- Soil probe: moisture 0-100%, ±3% for 0-53% and ±5% above; soil temp -40 to +80 °C, ±0.5 °C; supply 3-36 V DC
- Energy meter: class 1 (±1%), registers mostly 2-word values, scaling such as divide-by-100 for volts
- Packaged sensor dimensions: [PLACEHOLDER]
- Interface / connector details: [PLACEHOLDER: keyed harness, WHAN part number]
- SIM assignment: SIM5, ESP32 with RS485 transceiver, acts as Modbus master

**Narration:**
Here is the technical card, in two halves: the shared interface and the instrument-specific numbers. The interface: two signal wires named A and B, half-duplex, meaning devices take turns talking. Our kit runs the common default of 9600 baud. Every Modbus frame ends with a CRC-16 checksum, so a corrupted frame is detected and discarded rather than mistaken for data, a point the validation labs will return to. Now the instruments. The soil probe reports volumetric moisture from 0 to 100%, with accuracy of plus or minus 3% up to 53% moisture and plus or minus 5% above that: an honest datasheet admitting the sensor is better in dry soil than saturated soil. It also reports soil temperature from -40 to +80 degrees Celsius within half a degree, and accepts any supply from 3 to 36 volts. The energy meter is a class 1 instrument, meaning 1% accuracy on energy, and its register map stores most values as two 16-bit words with a documented scale factor, for example divide the raw voltage register by 100 to get volts. The packaged dimensions and the keyed connector details are placeholders for now and will be supplied with the final hardware. SIM5 carries the RS485 transceiver and the master firmware.

## Slide 05.7: Climate Change Applications

**Slide content:**
- Measurement: energy metering is the ground truth for any building decarbonisation claim
- Mitigation: register-level power data drives load scheduling, waste detection, and efficiency retrofits
- Adaptation: soil probes underpin irrigation scheduling as rainfall becomes less predictable
- Grid transition: the same Modbus skills read solar inverters, battery systems, and EV chargers
- Industrial instruments make climate action auditable, not estimated

**Narration:**
Why does an industrial interface matter for climate change? Because climate action lives or dies on measurement, and the world's energy and water infrastructure already reports through Modbus registers. Start with mitigation. Buildings cannot cut what they do not meter: the energy meter in this kit is the same class of instrument a facility manager uses to find the air conditioner that runs all night, the corridor lights burning through a sunny afternoon, the phantom loads that add up to 10 or 15% of a campus bill. Every kilowatt-hour you can attribute, you can challenge. Adaptation runs through the soil probe. As rainfall grows less predictable, irrigation must switch from calendar-driven to data-driven, and a buried probe reporting real moisture is what makes that switch trustworthy at farm scale. Then there is the energy transition itself: solar inverters, battery management systems, and EV chargers overwhelmingly expose their data over Modbus, so the register-reading skill you learn here is exactly the skill needed to verify a rooftop solar array is delivering its promised generation. The deeper point: climate claims need audit trails. An instrument with a register map, an accuracy class, and a timestamped log turns a sustainability estimate into evidence.

## Slide 05.8: Fusion Partners

**Slide content:**
- SCT-013 clamp: independent cross-check of the energy meter; agent flags divergence between the two
- SEN0193 capacitive probe: calibration transfer, lab-grade RS485 probe calibrates the low-cost sensor
- DS18B20: ambient temperature context for energy consumption patterns
- JSN-SR04T: tank level plus pump energy gives litres-per-kilowatt-hour pumping efficiency
- Agent workflow: `query_timeseries` on both sources, reconcile on tick, report disagreement with evidence

**Narration:**
The most instructive fusion in the whole kit is pairing the RS485 energy meter with the SCT-013 current clamp on the same circuit, because it teaches measurement disagreement. The meter is a class 1 instrument; the clamp is a low-cost transformer whose reading depends on jaw closure and ADC quality. An agent calling query_timeseries on both, reconciling on the tick counter, should see them agree within a few percent. When they drift apart, something real happened: the clamp jaw worked loose, or the load's power factor shifted, since the clamp sees apparent current while the meter computes true power. Deciding which instrument to trust, and why, is the validation skill this course exists to teach. The second fusion is calibration transfer: bury the RS485 soil probe next to the cheap SEN0193 capacitive sensor, let an agent regress one against the other over a week of wetting and drying, and you have promoted a 300-rupee sensor to near-reference behaviour, with the regression stored as an annotation. Add the DS18B20 for ambient temperature context on energy data, and the ultrasonic tank sensor to divide litres delivered by kilowatt-hours consumed, which turns a water pump into an efficiency experiment.

## Slide 05.9: Capstone C8: The Machine's Electrical Signature

**Slide content:**
- Question: what does the machine's electrical signature say before it fails?
- Sensors: RS485 energy meter, SCT-013 clamp, SPL microphone, DS18B20 on the motor casing
- Build a baseline: power, current waveform behaviour, acoustic level, casing temperature
- The contradiction: meter says power is normal, clamp and microphone say the load is changing
- Decision: schedule maintenance now, or certify the machine healthy for another month
- Agents run scheduled watchdog queries and open annotated alerts, never silent actuation

**Narration:**
The capstone question: what does a machine's electrical signature say before it fails? Pick a real rotating machine, a water pump or a workshop fan. Instrument it four ways: the RS485 energy meter on its supply, the SCT-013 clamp on the same conductor, the SPL microphone beside it, and a DS18B20 strapped to its casing. Spend the first week building a healthy baseline: what power it draws, how steady the current is, what it sounds like, how warm it runs. Then watch for drift. A failing bearing raises friction, which raises current a few percent at the same load, and raises acoustic level, days or weeks before the casing temperature responds, because heat is the lagging indicator. Here is the contradiction you must resolve: the energy meter, averaging over seconds, may report power as normal while the clamp's raw samples and the microphone both show growing fluctuation. Which evidence wins, and what threshold justifies spending money on maintenance? Your deliverable is a decision, not a dashboard: either a maintenance order with the evidence attached, or a signed statement that the machine is healthy, with the baseline to prove it. A watchdog agent runs the queries nightly, checks drift against the sensor cards, and opens an annotated alert; the decision to act stays human.
