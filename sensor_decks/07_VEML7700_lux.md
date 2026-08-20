# Sensor 07: VEML7700 - Illuminance / Lux (SIM2, I2C)

## Slide 07.1: AI-First: The Old Way and the New Way

**Slide content:**
- The old way: a person glances at a light meter, then forgets it
- Meanwhile corridor lamps burn at noon beside bright windows
- The new way: an AI compares light to a target, all day
- A corridor needs about 300 lux; sunlight often provides it free
- Light plus a target equals a decision: lamps on, off, or dimmed

**Narration:**
Picture a campus corridor at noon. Sunlight pours through the windows, and every ceiling lamp is burning anyway. Nobody decided that; the lamps are on a schedule, and no person stands there with a light meter asking whether they are needed. That is the old way: light is a number someone could read, occasionally does read, and then forgets. The new way starts with a target. Lighting standards say a corridor needs about three hundred lux to be safe, a classroom five hundred. Once you have a target, every light reading becomes a small decision waiting to happen: is there already enough? On a sunny morning the answer is yes, for free, from the sun. An AI can hold the reading against the target all day long, the way a careful shopkeeper watches the till, and turn the lamps on, off, or partly down as the daylight shifts. A number alone is trivia. A number with a target is a pending decision, and decisions are exactly what AIs are for. Your role in this deck: you define what enough light means, and the AI holds the building to your definition.

## Slide 07.2: AI-First: What the AI Must Know About This Sensor

**Slide content:**
- An AI is only as good as what it knows about its senses
- This sensor sees an enormous range: moonlight to full sunlight
- The reading is light at the sensor, not the whole room
- Where it is mounted changes what its number means
- Zero at noon means a covered or failed sensor, not darkness; its ID card teaches the AI such warnings

**Narration:**
Before the AI can act on light, it must understand this sensor's character, because an AI is only as good as what it knows about its own senses. Three facts matter. First, the range is enormous: this little chip can register moonlight and also full sunlight, roughly from a thousandth of a lux to over a hundred thousand. One device can judge a dark stairwell and a sunlit atrium. Second, the number is honest but local. The sensor reports the light falling on itself, not on the whole room. It is like a thermometer held in your hand: it tells you the temperature where it is, nothing more. A sensor facing the window and a sensor facing the wall will disagree, and both are right. So where you mount it is part of the design, and that mounting note travels with the sensor's ID card, the small file the AI reads before trusting any reading. Third, some readings are alarms in disguise. Zero lux at noon on an outdoor sensor does not mean the world went dark; it means the sensor is covered, dusty, or dead, and the AI's first duty is to say so rather than switch on every lamp on campus.

## Slide 07.3: The Agentic Pattern: The Agent Writes the Rule

**Slide content:**
- The pattern in one line: the AI writes the recipe once; the kitchen runs without it
- You state the goal: lights only when actually needed
- The AI turns it into a tiny rule: enough daylight, lamps off
- The rule runs by itself, even with no internet
- Later the AI returns as inspector and reports the savings

**Narration:**
This deck's pattern is called The Agent Writes the Rule, and it corrects the most common mistake people make with AI: putting it where a simple rule belongs. Think of a thermostat. Nobody stands by the heater all day adjusting it; someone set a rule once, and the device follows it faithfully. We use AI the same way. You tell the AI your goal in plain words: light the corridor properly, but never fight the sun. The AI turns that into a tiny rule: if daylight already meets the target, keep the lamps off; otherwise top up just enough. A person approves the rule, and from then on it runs on the small computer by itself. No internet, no AI in the loop, nothing to fail at midnight. The AI's second job comes later. It returns as an inspector, compares the electricity used before and after the rule, and tells you honestly what was saved. So the split is clean, and it is the deepest habit this course teaches: you set the goal, the AI writes and later checks the rule, and the rule does the running. Keep that split in mind as we now meet the light sensor itself.

## Slide 07.4: What It Is

**Slide content:**
- Vishay VEML7700: a digital ambient light sensor reporting calibrated illuminance in lux
- Inside: a photodiode behind a photopic filter, plus a 16-bit ASIC doing the conversion
- The filter shapes the response to match the human eye, so it measures light as we see it
- Dynamic range 0.0036 to 120,000 lux: moonless night to direct sunlight, one device
- Configurable gain and integration time; the SIM firmware auto-ranges
- Not a camera and not the kit's solar cell: it reports a number, not an image or power

**Narration:**
The VEML7700 answers a question your eye answers constantly but numbers rarely do: how bright is it here, really? Inside the chip, light falls on a photodiode and generates a current. Two refinements turn that into a proper instrument. First, an optical filter in front of the photodiode reshapes its sensitivity to match the human eye's daytime response, called the photopic curve, so the sensor weights green strongly and infrared barely at all, just as you do. That is why its output unit is the lux, the unit of illuminance as humans experience it, rather than raw optical power. Second, an integrated 16-bit converter with adjustable gain and integration time digitises the signal, giving the device an enormous usable span: from 0.0036 lux, dimmer than moonlight, to 120,000 lux, full tropical sun. Contrast this with the simple photovoltaic irradiance sensor in the Rev5 kit: that device reports the energy in sunlight and saturates quickly, telling you about power, while the VEML7700 tells you about visibility. A cheap light-dependent resistor cannot do either job across this range; it saturates on any sunny day exactly where the interesting decisions live. On SIM2 it is one more I2C device on the shared bus, and the firmware auto-ranges the gain so students never chase settings.

## Slide 07.5: What It Does in Practice

**Slide content:**
- Lighting control: switch and dim artificial light against measured daylight
- Compliance: verify workplaces meet standards, IS 3646 asks 300 lux in corridors, 500 in classrooms
- Dusk and dawn detection for outdoor and security lighting, tracking seasons automatically
- Display and signage brightness adaptation; glare detection above approximately 2,000 lux at a desk
- Agriculture: daily light integral for crops, grow-light control, shade-cloth verification
- Security: a lux spike inside a sealed enclosure means the enclosure was opened

**Narration:**
Where does a lux sensor earn its keep? Anywhere electric light and daylight negotiate. The classic job is lighting control: a corridor with big windows may already sit at 600 lux at 11 in the morning, and every fixture burning through that hour is pure waste. A calibrated lux reading lets a controller switch or, better, dim lights against what daylight already provides. The second job is compliance. Indian Standard 3646 and its international cousins specify illumination by task: roughly 300 lux for corridors, 500 for classrooms, 750 for fine work. Facilities teams currently verify this, if ever, with a hand-held meter once a year; a logging sensor verifies it continuously and finds the dark stairwell that becomes a safety report. Outdoors, a lux threshold beats a timer for streetlights because it tracks seasons and storms without being told. In agriculture, integrating lux across the day yields the daily light integral, the photon dose a crop actually received, which drives grow-light and shading decisions. And one elegant security trick from the additional-sensors study: put a VEML7700 inside a sealed equipment box. It should read zero forever. The moment it reads anything else, someone opened the box, and the timestamp is your tamper log.

## Slide 07.6: Technical Card

**Slide content:**
- Measurand: illuminance, lux; 16-bit resolution
- Range: 0.0036 to 120,000 lux across gain and integration-time settings
- Accuracy: approximately ±10% typical against a reference meter, after gain calibration
- Original package: 6.8 × 2.35 × 3.0 mm SMD, transparent top; I2C output, address 0x10
- Supply: 3.3 V from SIM2; microamp-level consumption, negligible on a power bank
- Packaged sensor dimensions: [PLACEHOLDER]; window material affects reading, calibration follows enclosure
- Interface / connector details: [PLACEHOLDER: keyed harness part number]; SIM assignment: SIM2 (I2C)

**Narration:**
The card in numbers. The measurand is illuminance in lux, delivered as a 16-bit digital value over I2C at address 0x10, so there is no analog chain for the student to condition and no conversion to perform. The span runs from 0.0036 lux to 120,000 lux, but not in one gulp: the sensor trades gain against integration time, and the SIM firmware walks those settings automatically, using long integration in near-darkness and short in sunlight. Absolute accuracy is approximately plus or minus 10% against a reference lux meter once gain is calibrated, moderate confidence, and here packaging matters more than silicon: our enclosure must present a clear or diffusing window in front of the die, and whatever that window absorbs becomes a systematic offset. The calibration constant therefore belongs to the packaged sensor, not the bare chip, and it lives in the sensor card where the agent can read it. The raw device is tiny, under seven millimetres long, with a transparent lid; final packaged dimensions and the keyed connector are placeholders pending production. Power draw is microamps, invisible next to the ESP32. One field note: mount the sensor facing what you want to measure, the working plane, not the light fitting; a sensor staring at a lamp measures the lamp.

## Slide 07.7: Climate Change Applications

**Slide content:**
- Lighting is roughly 15-20% of global building electricity
- Daylight harvesting: E_artificial = max(0, E_target − E_natural), dimming against free light
- Documented savings of 30-60% on lighting energy depending on glazing and orientation
- Rule of thumb approximately 120 lux per W/m², so lux also proxies solar heat gain for HVAC models
- Adaptation and ecology: cloud-cover quantification, seasonal daylight records, light-pollution baselines

**Narration:**
The climate argument is arithmetic. Lighting takes roughly 15 to 20% of the electricity used in buildings worldwide, and unlike heating, its waste is instantly recoverable: switch off or dim, and the saving is immediate, with no thermal lag and no comfort penalty when daylight already covers the need. The control law fits on one line: required artificial light equals the target level minus measured natural light, floored at zero. That is the daylight-harvesting equation, and standards bodies report it saves 30 to 60% of lighting energy in daylit buildings, the spread depending on windows and orientation. What makes the saving honest is that it is measurable with this same kit: log natural light for a semester, count the occupied hours where daylight alone met the standard, multiply by fixture wattage, and you have kilowatt-hours that a finance committee will accept. The sensor also serves the thermal side: sunlight is heat, and with the rough conversion of 120 lux per watt per square metre, a lux trace approximates the solar gain loading a room before the temperature sensor feels it, giving HVAC models an early input. Beyond buildings, a semester of sky readings quantifies cloud cover against a clear-sky model, builds a seasonal daylight record, and, at night, measures artificial light at night, a growing ecological concern the 0.0036 lux floor is sensitive enough to capture.

## Slide 07.8: Fusion Partners

**Slide content:**
- PIR: the complete lighting rule, lights on only when motion AND lux below threshold
- SCT-013 on the lighting circuit: measured kWh proves the daylight-harvesting saving
- BME688 humidity: lux drop plus humidity spike reads as fog, not cloud
- SCD41 or reed: occupancy and window state complete the "why is it bright or dark" picture
- Agent inference: cross-stream queries turn coincidence into explanation

**Narration:**
Alone, a lux sensor describes light; fused, it explains decisions. The first fusion fixes a real logic gap from the corridor-lighting project: motion sensing alone switches lights on at noon in a glass corridor. The correct rule needs both sensors: lights on only when motion is detected and measured lux sits below the corridor's 300 lux target. That single AND gate is the difference between a demo and a defensible energy policy, and an agent can author it in natural language and deploy it as a deterministic edge rule through deploy_rule. The second fusion closes the loop on money: clamp the SCT-013 around the lighting circuit, and the claimed saving becomes a measured kilowatt-hour difference between a baseline week and a harvesting week, queried by the agent from both streams and reconciled on the tick counter. The third fusion is subtler and shows what agents add: a midday lux collapse could be cloud, fog, or a failed sensor. Pull the BME688 humidity trace; lux down with humidity spiking near saturation reads as fog, lux down with humidity steady reads as cloud, lux at zero exactly while other kits nearby see daylight reads as a covered or failed sensor. That three-way disambiguation, run automatically through query_timeseries across sensors, is precisely the validation reasoning this course wants students to demand from their models.

## Slide 07.9: Capstone C2: Should the Lights Be On at All?

**Slide content:**
- Question: should the lights be on at all, and what did daylight save us?
- Sensors: VEML7700 at the working plane, PIR for presence, SCT-013 on the lighting circuit
- Week 1 baseline on existing switching; week 2 with the motion-AND-lux rule deployed at the edge
- The contradiction: lux says bright, PIR says occupied, meter says lights burning anyway
- Decision: adopt the rule campus-wide, adjust the threshold, or show the corridor never needs it
- Deliverable: measured kWh delta, compliance hours against IS 3646, payback estimate

**Narration:**
The capstone question sounds almost rude: should the lights be on at all? Choose a daylit corridor or reading room. Mount the VEML7700 at the working plane, a PIR covering the space, and the SCT-013 clamp on the lighting circuit at the distribution board. Week one, touch nothing: log daylight, presence, and lighting power under the building's existing habits. The data will contain the contradiction that drives the project: hour after hour where measured lux already exceeds the 300 lux standard, presence is intermittent, and the meter shows every fixture drawing full power. Week two, deploy the fix: a deterministic edge rule, lights on only with motion and lux below target, authored with your agent in natural language, reviewed by a human, and installed through deploy_rule so it runs without any model in the loop. Then let the agent do the accounting through query_timeseries: kilowatt-hours week over week, hours of standard-compliance before and after, false-offs where the rule darkened an occupied space, and the payback period on the sensor hardware at campus tariffs. The decision at the end is real: recommend the rule for rollout with measured savings, retune the threshold, or, if daylight never sufficed, say so with a semester of evidence. Either way, the lights answer for themselves.
