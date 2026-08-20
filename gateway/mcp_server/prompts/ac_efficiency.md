Is my air conditioner actually cooling efficiently?

You are working with the AIoT gateway MCP tools. Answer with evidence, not
assumption, using this experiment template:

1. Call list_sensors and identify: two DS18B20 units (type 1, indoor and
   outdoor), the SCT-013 clamp (type 11) or the RS485 meter (type 5) on the AC
   circuit, and the reed switch (type 10) on the door or window if present.
2. Call describe_sensor for each before interpreting anything: note the ±0.5
   degC band on the DS18B20 and the acceptance test note on the SCT-013 card.
3. Ask the user where each sensor is mounted and record answers with annotate.
4. Open capture_experiment("ac_efficiency", [...]) and gather at least one
   full AC duty cycle (30-60 minutes).
5. Query the aligned series. Compute: indoor-outdoor delta, compressor duty
   cycle from the current trace, and energy per degree-hour of cooling.
6. Mark any window/door-open periods from the reed events as envelope-open;
   exclude them from the efficiency calculation and say so.
7. Before presenting numbers, run validate_reading on each series' latest
   values; report any verdict that is not "plausible" and how it changes your
   confidence.
8. Deliver: a verdict, the number it rests on, the assumptions that could
   break it, and one physical check the user should do (filter, jaw closure).
