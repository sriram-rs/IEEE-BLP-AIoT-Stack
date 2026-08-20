# SIM Firmware (production, handover to firmware team)

One codebase, five build environments, one per Sensor Interface Module. Each
sensor is an independent module compiled in or out by build flags, so every
SIM variant carries exactly the sensors its interface allows, from one source
tree. Implements Section 6 of `../../00_ARCHITECTURE_AND_CODE_STRUCTURE.md`.

## Build and flash (PlatformIO)

```
pio run -e sim1_onewire            # DS18B20
pio run -e sim2_i2c                # BME688 + SCD41 + VEML7700
pio run -e sim3_gpio               # PIR + reed + AT42QT1010
pio run -e sim4_analog             # 4-20mA + SPL + JSN + SCT013 + SEN0193 + water
pio run -e sim5_rs485              # Modbus energy meter
pio run -e sim2_i2c -t upload && pio device monitor -b 115200
```

## What the firmware team must do (in order)

1. **Pins:** edit `include/pins.h` only. Every GPIO the firmware touches is a
   macro there, per variant, overridable from `platformio.ini` with `-DPIN_X=n`.
   No other file names a pin.
2. **Verify the Modbus register map** in `src/sensors/rs485_meter_mod.cpp`:
   the slave address and two register addresses are marked PLACEHOLDER/VERIFY
   against the actual meter datasheet. The gateway serves the same map as an
   MCP resource; both sides must match one document.
3. **Integrate Bosch BSEC2** for the BME688 (`src/sensors/bme688_mod.cpp` has
   the handover note). Until then the module reports present-but-not-ok with
   zeroed fields; it never fabricates air quality numbers.
4. **Calibrate the SPL slope/offset** (`spl_mod.cpp`) on real hardware and
   consider moving the constants to NVS like the soil anchors.
5. **Set KIT_ID per assembled kit** in `platformio.ini` (or a per-kit build flag).

## Architecture the reviewers should hold the code against

- `include/sensor_module.h` is the module contract: `init()` returns presence,
  `sample()` fills a card-defined payload and returns acquisition health.
- `src/sensors/sensor_registry.cpp` is the only file that knows the module
  list. Adding a sensor = one module file + one registry pair + one build
  flag + one gateway card.
- `src/common/adv_builder.cpp` is the only place frame bytes are laid out.
  It must stay byte-identical with `gateway/core.py`; the rehearsal
  advertiser and `gateway/scanner/sim_source.py` are executable
  cross-references, and `python -m gateway run` is the integration test.
- Design rules enforced in `src/main.cpp`: the SIM measures, never
  interprets; every failure sets a status bit instead of producing plausible
  numbers; fault injection is first-class (`fault <type_id> stuck|offset|drop|none`
  on the serial console at 115200).
- No deep sleep, deliberately: power banks cut output under light load, and
  continuous advertising is the keep-alive. Revisit only with battery packs
  that guarantee low-current operation.

## Serial console

```
fault 1 stuck        # freeze DS18B20 payload (fault_injected bit set)
fault 1 none         # clear
status               # battery mV + active fault table
cal12 dry            # SEN0193: capture dry-air anchor (SIM4)
cal12 wet            # SEN0193: capture saturated anchor (SIM4)
```

## Payload contract (byte-exact with the gateway cards)

| Type | Sensor | Payload layout (all little-endian) |
|---|---|---|
| 1 | DS18B20 | i16 temp_c*100 |
| 2 | BME688 | i16 t*100, u16 rh*100, u16 hPa*10, u16 iaq*10, u16 eco2, u16 bvoc*100 |
| 3 | PIR | u8 motion, u16 event_count |
| 4 | 4-20 mA | u16 loop_ma*100, i16 value*100 |
| 5 | RS485 meter | u16 v*100, u16 power_w, u32 kwh*100 |
| 6 | SCD41 | u16 co2_ppm, i16 t*100, u16 rh*100 |
| 7 | VEML7700 | u32 lux*100 |
| 8 | SPL | u16 db*10 |
| 9 | JSN-SR04T | u16 distance_mm |
| 10 | Reed | u8 open, u16 transitions |
| 11 | SCT-013 | u16 irms_a*1000, u16 va |
| 12 | SEN0193 | u16 raw_mv, u16 pct*10 |
| 13 | Water trace | u8 wet, u16 raw_mv |
| 14 | AT42QT1010 | u8 present, u16 touch_count |

## Integration test chain

1. Flash any variant; watch `[sim] selftest ...` and `[sim] adv ...` lines.
2. `python -m gateway run` on a laptop: sensors appear with delivery ratios.
3. `fault <type> stuck` on the console; catch it from data via the gateway's
   `validate_reading` (the adversarial validation lab, end to end).
4. The rehearsal advertiser (`../rehearsal_advertiser/`) is the known-good
   radio reference if a variant fails to appear: if the rehearsal sketch is
   received and the SIM build is not, the fault is in the SIM build, not the
   laptop.
