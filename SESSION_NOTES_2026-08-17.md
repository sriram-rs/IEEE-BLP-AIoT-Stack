# Session Notes — 2026-08-17

Personal working notes from a Claude Code session (Windows machine), carried
over so a fresh session (e.g. on Linux) has this context without
re-explaining. Not part of the official handover doc set (00-18).

## Where I am

- Sensor in hand: a **DS18B20+** (one-wire). This maps exactly to the
  existing kit: `sensor_type_id 1`, **SIM1** (One-Wire variant), card at
  `gateway/cards/01_ds18b20.json`, firmware module already implemented at
  `firmware/sim-firmware/src/sensors/ds18b20_mod.cpp`, build target
  `sim1_onewire` in `firmware/sim-firmware/platformio.ini`.
- Sensor is physically wired up already. Per `include/pins.h`: one-wire data
  line on **GPIO4**, needs a 4.7k pull-up to 3.3V.
- Not yet done: building/flashing the firmware, running the gateway, full
  signal-chain verification.

## Open question raised to Ratna Madam

I was told: "no calculations on the sensor side; broadcast raw data; the
gateway will be tuned to parse the raw advertisement and put it in the DB."

**I checked the entire handover directory (architecture doc, all firmware
source, the gateway decoder, and the full design conversation log) — there is
no trace of this anywhere.** What's actually implemented is the opposite,
stated as an explicit design rule:

> "The SIM never interprets, it measures. Conversion to engineering units
> happens in firmware... validation, fusion, and inference belong to the
> gateway and agents." — `00_ARCHITECTURE_AND_CODE_STRUCTURE.md:156`

Today, the firmware converts to real engineering units (°C, ppm, lux, A...)
and packs them as scaled fixed-point integers; the gateway's `decode()` in
`gateway/decoder/registry.py` just does `raw * scale` to unpack that
fixed-point integer back to a float. It is not deriving readings from raw
ADC counts or raw bus bytes anywhere.

**If the "raw broadcast, gateway computes" direction is confirmed as a real
change**, it is not a small tweak — it touches every sensor module, every
card's `payload_field`, and the gateway's decode logic, and per the
architecture doc's own contract rule it requires a `schema_version` bump
across the board, not a quiet edit. Waiting to hear back from Ratna Madam
before treating this as the design of record.

## Concept clarified this session: "measure, never interpret"

Converting a raw signal to engineering units (e.g. voltage → °C) is not
"interpretation" as long as it's a **deterministic function of the sensor's
own known physics/calibration alone** — same raw input always gives the same
output, no outside context needed. Examples in this codebase:

- DS18B20's own chip converts its internal voltage to °C via a factory
  calibration curve — the firmware just reads the finished digital value.
- The 4-20mA module's `RANGE_LO + (mA-4)/16*(RANGE_HI-RANGE_LO)` is fixed by
  the transmitter's own datasheet range, not by any judgment call.

**Interpretation** is a judgment that needs context beyond the sensor:
history, other sensors, a stated goal/threshold, human-supplied context.
That's reserved for the gateway/agents — `validate_reading`, fusion recipes,
`deploy_rule`.

The one nuance: firmware *does* flag known self-diagnostic fault signatures
(DS18B20 exactly 85.00°C = power-on reset default; 4-20mA below 3.8mA =
live-zero wiring fault). This is still "measurement," not interpretation,
because it's a documented fact about the sensor/loop's own known failure
mode, not a judgment about the world — and critically, the firmware still
forwards the raw value *and* the fault flag, rather than discarding or
replacing it.

## Next steps (not yet started)

1. Set up PlatformIO on the Linux machine.
2. `pio run -e sim1_onewire -t upload` with the DS18B20 wired to GPIO4 (4.7k
   pull-up to 3.3V).
3. Serial console at 115200 baud — expect `[sim] selftest DS18B20 ... -> OK`
   then `[sim] adv type=1 seq=... status=...` lines.
4. `python -m gateway run` on any machine with a BLE radio in range — confirm
   the sensor appears with a delivery ratio.
5. Try `fault 1 stuck` on the serial console; confirm the gateway's
   `validate_reading` catches it.

Reference docs, in order: `16_AGENTIC_ARCHITECTURE_BRIEF_FOR_FIRMWARE_TEAM.md`
section 6 (practical checklist), `firmware/sim-firmware/README.md` (build/
flash/console commands), `gateway/README.md` (running the gateway).
