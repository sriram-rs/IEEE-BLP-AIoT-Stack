# Sensor 13: RadioStudio Bare-Trace PCB - Water Presence / Level (SIM4, Analog, resistive)

## Slide 13.1: AI-First: The Old Way and the New Way

**Slide content:**
- This sensor says "dry" for months; one wet hour is why it exists
- The old way: someone spots water on the floor, usually too late
- The new way: an AI watches for that hour and never gets bored
- Water under a rack at 2 a.m. is caught at 2 a.m., not at 9
- This deck: how an AI stands guard over a rare event

**Narration:**
This little board spends almost its whole life saying one word: dry. It may say nothing else for months. So why is it in the kit? Because of the one hour when the answer changes: water creeping under an equipment rack, a leaking pipe in a store room, a blocked drain in a cold store. The old way of catching that hour is a person noticing the puddle, and people notice puddles late. Nobody checks a dry floor every ten minutes, and certainly not at two in the morning. The new way: an AI watches this sensor continuously. It is never bored by months of good news, never distracted, never asleep. If the floor turns wet at 2 a.m., the alarm happens at 2 a.m., not when the first person walks in at 9. That is the promise of this deck: a rare event, guarded around the clock, by something that does not mind the waiting. But standing guard raises a hard question about trust, and that question is the next slide.

## Slide 13.2: AI-First: What the AI Must Know About This Sensor

**Slide content:**
- An AI is only as good as what it knows about its senses
- It reads the sensor's ID card: what this board says, and how it fails
- Wetting is noticed within a second; drying takes minutes
- The trap: a dead sensor and a dry floor both send nothing
- So the AI must also check that the sensor itself is alive

**Narration:**
An AI has no eyes and no hands. Everything it knows about this floor arrives through this one small board, so it had better know exactly how far to trust it. That knowledge comes from the sensor's ID card, a small file the AI reads: what the board reports, how quickly, and how it fails. Two facts on that card matter most. First, the board is quick to say wet, within about a second, but slow to say dry again, because the water film takes minutes to evaporate. So the AI should not conclude the flood is over the moment the mopping starts. Second, and far more important, the trap: if the cable is cut or the board dies, it sends nothing. And nothing is exactly what a healthy board on a dry floor sends too. Silence from a live sensor and silence from a dead one look identical. A guard you cannot tell apart from an empty chair is no guard at all. What the AI does about that is this sensor's pattern, and it comes next.

## Slide 13.3: The Agentic Pattern: Is Silence Good News?

**Slide content:**
- The pattern: silence means "all clear" only if the sensor is alive
- Like pressing the test button on a smoke alarm
- You do not wait for a fire to find out the battery died
- The AI presses that button on a schedule, using a heartbeat signal
- You decide what silence must prove; the AI keeps checking

**Narration:**
The pattern this sensor teaches has a name shaped like a question: Is Silence Good News? In one line: never assume a quiet sensor is a happy sensor; check. You already know this pattern from home. A smoke alarm has a test button, and you press it now and then, because you do not want a fire to be the way you discover the battery died. But people forget to press it. An AI does not. Every message from this board carries a small counter, a heartbeat that keeps arriving even when the floor is bone dry. On a schedule, the AI checks: is the heartbeat still there, is the counter still counting? If yes, silence really does mean a dry floor. If the heartbeat stops, the AI raises a different alarm: not "water!", but "I have gone blind here, someone go and look." Notice the division of labour. You decide what silence has to prove and how often to test it; the AI does the tireless checking, day and night. Now let us look at the simple piece of copper this whole idea protects.

## Slide 13.4: What It Is

**Slide content:**
- The simplest sensor in the kit: a bare PCB with interdigitated copper traces, built by RadioStudio
- Two comb-shaped trace sets interleave without touching; dry, the resistance between them is effectively infinite
- Water bridging any pair of fingers drops the resistance sharply; a pull-up resistor converts that to a voltage the ADC reads
- Technically resistive, and that is the correct choice here: the sensor is dry in normal operation, so corrosion never accumulates
- Firmware duty-cycles the excitation voltage, energizing the traces only during a reading, to prevent electrolysis
- A deliberate teaching artifact: a bare PCB is a sensor; there is no chip at all

**Narration:**
What is the least amount of hardware that can still be called a sensor? This board is the answer, and RadioStudio built it for exactly that lesson. Look at it: two sets of copper fingers printed on a PCB, interleaved like clasped hands that never touch. Dry, no current can cross the gap, and the resistance between the two combs is effectively infinite. Put a drop of water across any two fingers and ions in the water carry current; the resistance collapses. A single pull-up resistor turns that resistance change into a voltage swing, and the SIM's analog input reads it. You may remember we rejected resistive sensing for the soil probe because of corrosion. Why is it right here? Because this sensor spends its life dry. It only gets wet in a fault condition, a leak or a flood, so electrolytic corrosion never has time to accumulate. The firmware adds one more protection: it energizes the traces only for the few milliseconds of each reading, rather than holding a DC voltage across wet copper continuously. There is no integrated circuit on this board at all. That is the point. Sensing is physics first, silicon second, and sometimes the physics is a pattern of copper and a puddle.

## Slide 13.5: What It Does in Practice

**Slide content:**
- Leak detection under equipment racks, server rooms, battery banks
- Basement and undercroft flood ingress: earliest possible warning at floor level
- Cold-storage defrost drain blockage: water backing up where it should drain away
- Rainwater tank and sump overflow: a trace strip at the overflow line
- Washing machine, water heater, and plumbing joint monitoring in facilities
- Graded response: mounted vertically, more fingers bridged means lower resistance, giving a coarse depth indication

**Narration:**
Where does a wet-or-dry sensor matter in the real world? Almost anywhere water appears that should not. The classic deployment is under equipment: server racks, battery banks, laboratory instruments. Water on that floor is a fault every single time, and the first centimetre of water does the same damage to electronics as the tenth, so early detection is everything. Facilities teams place these under water heaters, behind washing machines, and along known-troublesome plumbing joints. Cold rooms have a subtler failure: every defrost cycle produces meltwater that must drain away, and when the drain line blocks, water backs up silently until it reaches the stored food. A trace strip in the drain pan catches it on day one. At the other end of the water system, a strip mounted at a rainwater tank's overflow line reports the moment the tank starts wasting collected water. One refinement worth knowing: mount the board vertically and it becomes a coarse level gauge, because rising water bridges more fingers and the resistance keeps falling. It is not a precision instrument, but wet, ankle-deep, and knee-deep are distinguishable states, and for an emergency response that granularity is often enough.

## Slide 13.6: Technical Card

**Slide content:**
- Measurand: water presence (binary wet/dry), plus coarse level when mounted vertically
- Sensing element: interdigitated copper traces, ENIG finish, on FR4 PCB
- Output: resistance drop read as analog voltage via pull-up; dry reads near supply, wet reads low
- Response: wetting detected within one excitation cycle (approximately 1 s at default cadence); drying lags as the surface evaporates
- Excitation: duty-cycled by SIM4 firmware to prevent electrolysis; no continuous DC across traces
- Original form: RadioStudio bare PCB, approximately 30 x 10 mm sensing area (to be confirmed)
- Packaged sensor dimensions: [PLACEHOLDER]
- Interface/connector details: [PLACEHOLDER: keyed harness part number]
- SIM assignment: SIM4, analog ADC input

**Narration:**
The technical card for this sensor is short, and its shortness is instructive. The measurand is water presence: wet or dry, with a coarse level reading available in vertical mounting. There is no accuracy specification in the usual sense, because the sensor is a threshold device; the meaningful numbers are the dry reading, which sits near the supply rail through the pull-up, and the wet reading, which collapses toward ground. The firmware declares wet when the voltage crosses a midpoint threshold with hysteresis, so a single splash does not chatter between states. Response time going wet is essentially one excitation cycle, about a second at the default cadence. Going dry is slower and honest students will notice it: the board reads wet until the surface film evaporates, which can take minutes. That asymmetry is a property of the physics, not a fault, and the sensor card records it so an AI agent reasoning about the data knows a lingering wet reading after cleanup is expected. The excitation duty-cycling matters for longevity: the SIM powers the traces only during the measurement window, which prevents the electrolytic corrosion that would otherwise eat energized wet copper. Packaged dimensions and the keyed connector are placeholders pending the production design. The board connects to SIM4, the analog interface module.

## Slide 13.7: Climate Change Applications

**Slide content:**
- Adaptation headline: climate change intensifies short-duration rainfall; urban flash flooding is rising on every continent
- A distributed grid of trace sensors gives street-level, basement-level flood truth that rain gauges cannot
- Early warning: minutes of notice at floor level protects equipment, archives, switchgear, and lives
- Protecting mitigation infrastructure: battery storage, inverter rooms, and pump pits are flood-sensitive climate assets
- Water conservation: overflow detection at tanks stops collected rainwater from being wasted
- Measurement role: timestamped ingress events build a flood-frequency record for a building or campus

**Narration:**
The climate connection here is adaptation, and it is direct. A warmer atmosphere holds roughly seven percent more water vapour per degree of warming, and the observed result is more intense short-duration rainfall. Cities feel this as flash flooding: drainage designed for the old rainfall statistics meets the new statistics and loses. Rain gauges tell you what fell from the sky; they do not tell you which basements, pits, and equipment rooms actually took water. A grid of trace sensors, at tens of rupees per point, produces exactly that missing record: timestamped ingress events, location by location, storm by storm. Over a few seasons that becomes a flood-frequency map of a campus, which is the evidence base for deciding where drainage investment goes. The early warning role is immediate and human: water at floor level in a switchgear room or a records archive, detected in the first minute, is the difference between mopping and replacement. Notice also that climate mitigation infrastructure is itself flood-sensitive: battery banks, inverters, and pump pits all die in water, so the cheapest sensor in the kit stands guard over the most expensive equipment. And at the rainwater harvesting tank, overflow detection stops the quiet waste of water someone went to the trouble of collecting.

## Slide 13.8: Fusion Partners

**Slide content:**
- JSN-SR04T (ultrasonic level): trend and rate of rise; the trace PCB gives binary ground truth at a fixed height; two different physics, one conclusion
- Reed switch (door state): was the flood path a door left open, or a pipe? Sequence of events disambiguates
- SCT-013 (pump current): confirms the sump pump actually ran when water was detected; detects the failed-pump scenario
- BME688 (humidity): rising humidity plus a wet event distinguishes slow seepage from sudden ingress
- Agent inference via MCP: correlate wet events, level trends, pump current, and door state into a single narrated incident timeline

**Narration:**
On its own this sensor says one word: wet. Fusion turns that word into a story. Pair it with the JSN-SR04T ultrasonic sensor watching the same sump or basement from above and you get redundant detection through two unrelated physical principles: acoustic ranging and ionic conduction. An agent that sees the ultrasonic level rising and the trace strip going wet at the expected height can be confident this is real water, not a splash on one sensor or an acoustic artifact on the other. Redundancy with diverse physics is how safety-critical systems are built, and students see it here at hobby cost. Add the SCT-013 current clamp on the sump pump circuit and the agent can check the response, not just the event: water detected, did the pump draw current? A wet strip with a silent pump is the emergency case, and it is invisible to either sensor alone. The reed switch on the room door adds the causal question: did someone leave the door open before the storm, or did water come through the slab? In the MCP architecture, a watchdog agent subscribes to all four streams and, on a wet event, assembles the aligned timeline into a narrated incident report: what happened, in what order, what responded, and what needs a human.

## Slide 13.9: Capstone C5: Is the Restricted Zone Secure Against More Than One Threat?

**Slide content:**
- Question: can one room be defended against intrusion, equipment failure, and flood with a coherent sensor story?
- Sensors: reed (door), PIR (motion), VEML7700 (enclosure tamper), SCT-013 (equipment current), water level trace (flood)
- The trace PCB adds the fourth threat model: water, independent of every other signal
- Contradiction to resolve: a wet reading during mopping and cleaning versus genuine ingress; context distinguishes them
- Agents assemble multi-sensor incident timelines and classify: intrusion, fault, flood, or false alarm
- Decision at the end: an escalation policy that says who gets called, for what evidence, at what hour

**Narration:**
The capstone question sounds like security but is really about evidence: is this restricted equipment room protected against more than one kind of threat, and can the system explain what happened after the fact? Most monitoring projects defend against a single threat, intrusion, and go blind to everything else. This project instruments four: the reed switch watches the door, PIR watches for motion, the light sensor inside the sealed cabinet catches tampering, the current clamp watches equipment health, and the trace PCB under the rack watches for water, the threat none of the others can see. The contradiction students must resolve is the honest one: the cleaning crew mops this floor twice a week. A wet reading at 10 a.m. with the door properly opened, motion in the room, and the mop bucket's signature brief wetting is not a flood. A wet reading at 2 a.m., door closed, no motion, level still rising ten minutes later, is. Writing the rule that separates them, and letting the agent argue its classification from the aligned timeline, is the heart of the exercise. The deliverable is an escalation policy with evidence requirements: which combination of signals pages the warden at night, which waits for morning, and what the agent must include in its incident narrative either way.
