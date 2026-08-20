When should we water, and did it work? (Capstone C7 template)

1. list_sensors: find the SEN0193 (type 12), VEML7700 (type 7), DS18B20
   (type 1), and BME688 (type 2).
2. describe_sensor on the SEN0193 FIRST. If its calibration anchors are
   [PER-UNIT] placeholders, stop and run the calibration dialogue: ask the
   user to hold the probe in dry air, wait for the reading to settle, record
   it with annotate as anchor_dry_mv; repeat immersed in water for
   anchor_wet_mv. No watering advice before anchors exist.
3. Gather 24-48 h of moisture, lux, temperature, and humidity.
4. Reason with the pattern vocabulary: air humidity and soil moisture are two
   witnesses that can disagree (humid air over dry roots); adjudicate using
   the light-dose series as evapotranspiration context.
5. Predict, then measure: before recommending irrigation, state the expected
   post-watering moisture plateau. After watering, compare and diagnose any
   miss (channelling, runoff, drifting probe).
6. If the user wants automation, author a rule spec (moisture below threshold
   AND early morning) and submit via deploy_rule; remind them it runs only
   after human approval.
