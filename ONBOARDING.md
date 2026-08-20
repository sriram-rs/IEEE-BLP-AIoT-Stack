# Onboarding: Migrating SIM Firmware Repos to the Architecture Contract

For whoever's picking up the next sensor (and their Claude session). This
captures the playbook and the gotchas from migrating `IEEE-BLP-
TemperatureSensor` (DS18B20 / SIM1) and `IEEE-BLP-GasSensor` (BME688 / SIM2)
to the course architecture contract, so the next one goes faster.

## Read first

1. `00_ARCHITECTURE_AND_CODE_STRUCTURE.md` — Section 4 (BLE payload spec)
   and Section 6 (firmware design rules) are the actual contract. Everything
   below exists to satisfy those two sections.
2. `gateway/core.py` — the `HEADER` struct is the byte-for-byte source of
   truth for the frame layout. If your firmware and this disagree, the
   firmware is wrong, not the other way round.
3. `gateway/cards/0N_<part>.json` for your sensor — the payload_field
   offsets/encodings/scales are the contract for *your* sensor specifically.
   Read this before writing a single line of firmware.
4. `SESSION_NOTES_2026-08-17.md` — background on why "measure, never
   interpret" isn't the same as "broadcast raw ADC counts," if that
   distinction comes up again with a stakeholder.
5. The two completed migrations as worked examples — read their commits,
   not just their final state, to see the debugging trail:
   - `IEEE-BLP-TemperatureSensor` commit `1909fe6` (dev-pf-migration)
   - `IEEE-BLP-GasSensor` commit `da6b947` (dev-pf-migration)

## The pattern (what "contract compliance" means concretely)

Every SIM firmware repo in this kit is a standalone ESP-IDF project (not
PlatformIO — that's the separate `ai_first_course/firmware/sim-firmware`
*reference/simulator* repo, which is useful to read but is not what ships).
Each real board repo needs the same five pieces added, regardless of sensor:

1. **`Modules/Inc/Contract.h`** — company_id/kit_id/sensor_type_id/
   schema_version/seq/tick_ms/status layout + `Contract_PutU16/I16/GetU16/
   I16` little-endian packing helpers. Copy this near-verbatim from either
   completed repo; only `CONTRACT_SENSOR_TYPE_*` changes per sensor.
2. **`Modules/{Inc,Src}/SeqStore.{h,c}`** — NVS-persisted per-sensor-type
   `seq` counter. Copy verbatim; it's generic over `type_id` already.
3. **`Modules/{Inc,Src}/FaultInject.{h,c}`** — instructor console (`fault
   <type_id> stuck|offset|drop|none`, `status`). Copy the GasSensor version
   (operates on a raw payload buffer of any width), not the
   TemperatureSensor version (which was hand-specialized to a single int16
   field before we realized the generic version was cleaner and more
   faithful to `sim-firmware`'s own `fault_inject.cpp`).
4. **`BLE.c/h` rewritten** around `BLE_PublishFrame(sensor_type_id,
   schema_version, seq, tick_ms, status, payload, payload_len)` replacing
   whatever ad hoc `BLE_UpdateAdvertisement()` existed before. Check
   `include_name` — see the 31-byte budget gotcha below before assuming
   `true` is fine.
5. **The sensor-reading module rewritten** to a `SensorX_Sample(uint8_t
   *payload, uint8_t *len, bool *sensor_ok)` shape: fill payload exactly per
   the card's `payload_field` offsets/scales, set `*sensor_ok` only for a
   genuine trustworthy reading, never fabricate a plausible number on
   failure (zero-fill or a documented sentinel instead). `main.c` becomes:
   `sample -> status bits -> FaultInject_Apply -> SeqStore_Next ->
   BLE_PublishFrame`, looped at whatever cadence the *sensor* actually needs
   (see gotcha below — this is not always the card's `sampling_period_s`).

**Decide payload scope explicitly, don't default to "keep everything the
old firmware sent."** Existing boards often broadcast more fields (or
differently-encoded ones) than the card defines. Match the card exactly
unless there's a real reason to extend it (extending the card is a
cross-repo change to the shared gateway, not just firmware — get a second
opinion before doing that). If a signal genuinely matters but isn't in the
card's payload_fields (e.g. BME688's IAQ accuracy), look for a way to fold
it into an existing mechanism (we used `status.sensor_ok`) rather than
inventing a new wire field unilaterally.

## Toolchain gotchas

- **Use ESP-IDF v5.4.1, not v5.5.3.** v5.5.3 has a real upstream bug:
  `esp_bt.h` for the ESP32 target includes a relative path
  (`../../../../controller/esp32/esp_bredr_cfg.h`) that doesn't resolve
  given that release's own directory structure. Any file including
  `esp_bt.h` fails to build. v5.4.1 doesn't have this include at all.
  Confirmed by diffing the header between the two tags on GitHub before
  concluding it wasn't our config.
- **These repos have no committed `sdkconfig`** (gitignored, as usual for
  ESP-IDF). Bluetooth is off by default. Add `sdkconfig.defaults` with:
  ```
  CONFIG_BT_ENABLED=y
  CONFIG_BT_BLUEDROID_ENABLED=y
  CONFIG_BT_CONTROLLER_ENABLED=y
  CONFIG_BTDM_CTRL_MODE_BLE_ONLY=y
  ```
  If you add this file *after* a `sdkconfig` already got generated without
  it, delete the stale `sdkconfig` (safe, gitignored) so it regenerates
  incorporating the defaults — `idf.py build` won't retroactively apply
  `sdkconfig.defaults` to an existing `sdkconfig`.
- **A Contract.h comment containing a literal `/*` sequence** (e.g. writing
  `gateway/cards/*.json` inside a `/* ... */` doc comment block) trips
  `-Werror=comment` and fails the build. Innocuous but wastes a build
  cycle; word contract-layout comments to avoid the literal substring.
- **Vendor binary blobs are gitignored on purpose** (e.g. GasSensor's
  `libalgobsec.a`, matched by a blanket `*.a` rule). Don't fight that; it's
  almost certainly there for licensing/size reasons. Source your own copy
  locally and document where you got it in the README, same as we did.
  **Check the major version matches what the header/code expects** — BSEC1
  vs BSEC2 look similar (both called "BSEC," both ship as `libalgobsec.a`)
  but are API/ABI incompatible. If a sensor genuinely produces zeroed
  output with no error logged anywhere, check `bsec_get_version()`'s
  logged output against what the driver code's output-ID enum actually is
  (BSEC2-only IDs like `BSEC_OUTPUT_STATIC_IAQ`/`RUN_IN_STATUS` are a
  giveaway the code wants BSEC2).

## Hardware / serial gotchas

- **`ModemManager` looks like the culprit for "Could not exclusively lock
  port" but often isn't.** It's a real, common cause on Ubuntu with USB
  serial adapters, and stopping it (`sudo systemctl stop ModemManager`) is
  a reasonable first thing to try — but confirm with `fuser -v /dev/ttyUSBx`
  and `ps aux` first if it doesn't fix it. In one case here the actual
  holder was a colleague's `picocom` session on the same shared machine.
- **This kit's boards may need a manual physical reset after flashing.**
  `esptool`'s auto-reset via the RTS pin doesn't reliably bring some of
  these boards out of bootloader/into a running state — this happened
  consistently across multiple boards and multiple flash attempts, not a
  one-off. If a freshly-flashed board produces zero serial output and
  `esptool --after hard_reset chip_id` also fails to connect, ask whoever
  has physical access to reset it manually before concluding anything is
  broken in software.
- **Cheap/clone FT232R USB-serial adapters on this kit report identical
  factory-default serial numbers** (`ID_SERIAL_SHORT`). Don't use
  `udevadm ... ID_SERIAL_SHORT` to distinguish two boards on the same
  machine — it won't work. Use `lsusb` device-number timing as a weak
  hint, but confirm which port is which board with whoever has physical
  access before flashing, especially if a working board's firmware is at
  stake.
- **Opening a serial port with plain `stty`+`cat` or a naive
  `serial.Serial(port, baud)` can toggle DTR/RTS and either reset the board
  or hold it in reset**, producing either silence or corrupted/duplicated
  line noise (hundreds of identical garbled lines is a strong tell — don't
  mistake it for a firmware crash loop). A `pyserial` connection opened
  with `dtr=False, rts=False` explicitly is more reliable for a one-shot
  read of an already-running board.

## Verification method that worked

Don't trust any single channel alone; cross-check:

1. **Serial console** (`[sim] selftest ... -> OK`, `[sim] adv type=N
   seq=... status=0x..`) confirms the firmware's own view.
2. **`bleak` (Python) direct scan**, decoding the raw manufacturer-data
   bytes by hand against `Contract.h`'s offsets, confirms what's actually
   on the air — independent of the gateway/decoder, so it catches
   firmware-side bugs the gateway might mask or that a payload-format bug
   might hide from a casual look. This is how we caught the 31-byte
   advertisement truncation (serial log said one thing, the actual air
   bytes were 3 bytes short).
3. **The gateway itself** (`python -m gateway run`, dashboard at
   `:8931`, or `sqlite3`-free query via `python3 -c "import sqlite3;..."`
   against `gateway/data/gateway.db`) confirms end-to-end decode against
   the real card.
4. **Delivery ratio** (`gateway/decoder/reconcile.py`'s `seq`-gap
   accounting) is a genuine diagnostic, not just a metric — a low ratio
   with real hardware in range almost always means `BLE_ADV_INTERVAL_MS`
   is too slow relative to how often `seq` actually increments, not radio
   range. Rule of thumb: the advertising interval should be a small
   fraction (sim-firmware uses 100 ms) of however often you publish a new
   frame, so the radio gets many chances to send each `seq` before the
   next one replaces it.

## Sample cadence vs. poll rate — don't conflate them

The card's `sampling_period_s` describes how often a *new result* is
expected, which is a property of the sensor/algorithm. It is **not**
necessarily the rate your main loop should run at. BME688+BSEC needs
`bsec_sensor_control()` polled roughly every ~1 s regardless of the card's
5 s `sampling_period_s`, because BSEC uses call frequency to time its own
internal duty cycle — slow the poll loop down to match the card's period
and BSEC silently never triggers a measurement (no error logged anywhere,
just an all-zero payload forever). If a sensor has its own async/library-
driven timing like this, read its integration docs for the *required host
poll rate* separately from the card's *published result rate*.

## Git conventions for this project

- Each board repo needs its own **local** git identity
  (`git config user.name`/`user.email`) — it's not inherited from global
  config on this machine. Ask what identity to use before setting it;
  don't assume.
- Commit messages for this migration work should not carry Claude
  attribution (no `Co-Authored-By: Claude` trailer) — that's this
  engineering team's stated preference for this repo family, not a
  general rule.
- Claude commits; the human pushes. Don't push without being asked.

## Quick checklist for the next sensor

1. Read the card (`gateway/cards/0N_*.json`) and the relevant
   `sim-firmware/src/sensors/*_mod.cpp` reference for scale/offset intent.
2. Copy `Contract.h`, `SeqStore.{h,c}`, `FaultInject.{h,c}` from
   `IEEE-BLP-GasSensor` (the more general FaultInject version), changing
   only `CONTRACT_SENSOR_TYPE_*`.
3. Rewrite `BLE.c/h` around `BLE_PublishFrame`; check the 31-byte budget
   math before deciding whether `include_name` can stay `true`.
4. Rewrite the sensor module to the `Sample(payload, len, sensor_ok)`
   shape; decide payload scope against the card explicitly.
5. Rewrite `main.c`: sample -> status -> fault -> seq -> advertise, at
   whatever cadence the sensor's own integration actually needs.
6. Add `sdkconfig.defaults` (BT enabled, BLE-only controller mode).
7. Install/confirm ESP-IDF v5.4.1 (not v5.5.3).
8. Build, flash, verify via serial + bleak + gateway dashboard +
   delivery-ratio sanity check, in that order.
9. Update the README (payload spec table, fault console, toolchain notes).
10. Commit locally with the right git identity, no Claude attribution.
    Human pushes.
