# Rehearsal Advertiser

One ESP32 dev board pretending to be SIM1 with a DS18B20, broadcasting the
exact frame format the gateway parses. Purpose: prove the radio path and the
frame contract end to end before the workshop, the two things `python -m
gateway simulate` cannot prove.

## Flash it

Arduino IDE (or arduino-cli), board "ESP32 Dev Module", ESP32 core 2.x/3.x.
No libraries needed in the default synthetic mode. Open the sketch, select the
board's COM port, upload.

Real probe instead of synthetic values: set `USE_REAL_DS18B20` to `1`, install
the OneWire and DallasTemperature libraries, wire the probe's data pin to
GPIO 4 with a 4.7 kilo-ohm pull-up to 3V3.

## Rehearse

1. Board on USB power; open the serial monitor at 115200 to watch frames go out.
2. On the laptop: `pip install bleak`, then from `ai_first_course/`:
   `python -m gateway run`
3. Expected within ~10 seconds: `[gateway] 1:1 (DS18B20) online: temperature_c=...`
   and the sensor visible on the dashboard with a delivery ratio.
4. Walk away from the laptop with the board and watch the delivery ratio drop:
   that is the seq counter measuring real packet loss, the workshop's QoS lesson.
5. Type `f` in the serial monitor: the value freezes but keeps arriving.
   Ask Claude (via `python -m gateway mcp`) whether the sensor is healthy;
   `validate_reading` and the card's failure modes are the intended path to
   catching it.

## Pass criteria

The rehearsal passes when: the sensor appears on two different laptops
simultaneously, the delivery ratio is above ~90% at classroom range, and the
stuck fault is detectable from data alone. If reception fails on a specific
laptop, its Bluetooth radio or driver is the suspect: retry with a USB BLE
dongle before blaming the board.
