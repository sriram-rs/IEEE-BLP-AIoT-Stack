/*
 * rehearsal_advertiser.ino
 *
 * Minimal SIM stand-in for the workshop rehearsal: broadcasts BLE
 * advertisement frames in the exact format the gateway parses
 * (gateway/core.py). Flash this on any ESP32 dev board, run
 * `python -m gateway run` on a laptop, and the board should appear as
 * sensor 1:1 (DS18B20) within seconds.
 *
 * By default the temperature is SYNTHETIC (a slow sine wave around 26 C),
 * so the rehearsal needs no wiring at all: it tests the radio path and the
 * frame contract, which are the two things the simulator cannot test.
 * Set USE_REAL_DS18B20 to 1 to read an actual probe on GPIO 4 instead
 * (requires the OneWire and DallasTemperature libraries).
 *
 * Serial commands at 115200 baud, for the fault-injection labs:
 *   f  toggle "stuck" fault (payload freezes, fault_injected bit set)
 *   b  toggle the low-battery status bit
 *
 * Board support: "ESP32 Dev Module" in Arduino IDE / arduino-cli,
 * ESP32 core 2.x or 3.x (uses the classic BLE library bundled with it).
 */

#include <BLEDevice.h>
#include <BLEAdvertising.h>

// ---------- configuration: the knobs a workshop instructor may change ----------
#define KIT_ID          1        // kit this board belongs to; gateway can filter on it
#define SENSOR_TYPE_ID  1        // 1 = DS18B20 per the sensor card registry
#define SCHEMA_VERSION  1        // payload layout version, must match the card
#define PERIOD_MS       5000     // one new reading every 5 s, per the DS18B20 card
#define USE_REAL_DS18B20 0       // 0 = synthetic sine wave, 1 = real probe on ONE_WIRE_PIN

#if USE_REAL_DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_PIN 4           // data pin for the real probe (4.7k pull-up to 3V3 required)
OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature probes(&oneWire);
#endif

// ---------- frame constants: mirror gateway/core.py, do not change casually ----------
static const uint16_t COMPANY_ID = 0xFFFF;  // development company ID; gateway filters on it
static const uint8_t STATUS_SENSOR_OK      = 0x01;
static const uint8_t STATUS_LOW_BATT       = 0x02;
static const uint8_t STATUS_FAULT_INJECTED = 0x04;

// ---------- mutable state shared between loop iterations ----------
static uint16_t seq = 0;             // monotonic sequence counter; wraps at 65535, gateway handles the wrap
static bool faultStuck = false;      // serial-toggled: freeze the payload to teach stuck-value detection
static bool lowBatt = false;         // serial-toggled: exercise the low_batt status bit end to end
static int16_t stuckValue = 0;       // the frozen reading while faultStuck is active
static BLEAdvertising *advertising;  // handle reused every cycle; re-creating it leaks in ESP32 BLE

// Build the 13-byte manufacturer data body (11-byte header + 2-byte payload)
// exactly as gateway/core.py HEADER defines it: little-endian throughout.
static void buildFrame(uint8_t *buf, int16_t centiDegC) {
  uint8_t status = STATUS_SENSOR_OK;                     // a live reading always asserts sensor_ok
  if (lowBatt)    status |= STATUS_LOW_BATT;
  if (faultStuck) status |= STATUS_FAULT_INJECTED;       // instructor tooling sees the truth; students must find it from data
  uint32_t tick = millis();                              // monotonic since boot; gateway reconciles it against arrival time
  buf[0]  = KIT_ID & 0xFF;                               // kit_id, uint16 LE
  buf[1]  = (KIT_ID >> 8) & 0xFF;
  buf[2]  = SENSOR_TYPE_ID;                              // resolves the sensor card on the gateway
  buf[3]  = SCHEMA_VERSION;                              // lets old gateways detect newer payload layouts
  buf[4]  = seq & 0xFF;                                  // seq, uint16 LE: the silent-packet-loss detector
  buf[5]  = (seq >> 8) & 0xFF;
  buf[6]  = tick & 0xFF;                                 // tick_ms, uint32 LE
  buf[7]  = (tick >> 8) & 0xFF;
  buf[8]  = (tick >> 16) & 0xFF;
  buf[9]  = (tick >> 24) & 0xFF;
  buf[10] = status;
  buf[11] = centiDegC & 0xFF;                            // payload: temperature * 100, int16 LE per the DS18B20 card
  buf[12] = (centiDegC >> 8) & 0xFF;
}

// Produce the temperature reading for this cycle: real probe or synthetic wave.
static int16_t readTemperature() {
#if USE_REAL_DS18B20
  probes.requestTemperatures();                          // blocking conversion, ~750 ms at 12-bit; fine at a 5 s period
  float t = probes.getTempCByIndex(0);
  if (t == DEVICE_DISCONNECTED_C) return 8500;           // 85.00 C is the DS18B20 power-on default; the card lists it as a known bad reading, so surfacing it teaches exactly the right lesson
  return (int16_t)(t * 100.0f);
#else
  // Synthetic: 26 C base, +/-3 C over a 10-minute sine, so the dashboard visibly moves during a rehearsal
  float phase = (millis() % 600000UL) / 600000.0f;
  float t = 26.0f + 3.0f * sinf(phase * 2.0f * PI);
  return (int16_t)(t * 100.0f);
#endif
}

// Push a new frame into the advertisement payload and (re)start advertising.
static void advertiseFrame() {
  int16_t reading = readTemperature();
  if (faultStuck) {
    reading = stuckValue;                                // frozen value: looks plausible, moves never; only validate_reading or a suspicious student catches it
  } else {
    stuckValue = reading;                                // remember the last honest reading so a later 'f' freezes at something realistic
  }
  seq++;                                                 // one increment per reading, not per radio repeat: repeats of the same seq are how the gateway dedupes

  uint8_t frame[13];
  buildFrame(frame, reading);

  // Manufacturer Specific Data = 2-byte company ID + our frame; total AD stays well under the 31-byte legacy budget because we advertise no name
  String mfg;
  mfg += (char)(COMPANY_ID & 0xFF);
  mfg += (char)((COMPANY_ID >> 8) & 0xFF);
  for (int i = 0; i < 13; i++) mfg += (char)frame[i];

  BLEAdvertisementData adv;
  adv.setFlags(0x06);                                    // LE General Discoverable + BR/EDR not supported: the standard beacon flags
  adv.setManufacturerData(mfg);
  advertising->stop();                                   // payload can only be swapped while not advertising
  advertising->setAdvertisementData(adv);
  advertising->start();

  Serial.printf("[sim] seq=%u temp=%.2fC status=0x%02X%s\n",
                seq, reading / 100.0f,
                (uint8_t)(STATUS_SENSOR_OK | (lowBatt ? STATUS_LOW_BATT : 0) | (faultStuck ? STATUS_FAULT_INJECTED : 0)),
                faultStuck ? " (STUCK)" : "");
}

// Handle single-character fault-injection commands from the serial monitor.
static void pollSerial() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == 'f') {                                      // toggle the stuck-value fault
      faultStuck = !faultStuck;
      Serial.printf("[sim] stuck fault %s\n", faultStuck ? "ON" : "OFF");
    } else if (c == 'b') {                               // toggle the low-battery bit
      lowBatt = !lowBatt;
      Serial.printf("[sim] low_batt %s\n", lowBatt ? "ON" : "OFF");
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n[sim] rehearsal advertiser: DS18B20 frame on kit 1, type 1");
  Serial.println("[sim] serial commands: f = stuck fault, b = low battery");
#if USE_REAL_DS18B20
  probes.begin();                                        // start the One-Wire bus for the real probe
  Serial.println("[sim] using REAL DS18B20 on GPIO 4");
#else
  Serial.println("[sim] using SYNTHETIC temperature (no wiring needed)");
#endif
  BLEDevice::init("");                                   // empty name: keeps the advertisement small and anonymous, matching real SIM behaviour
  advertising = BLEDevice::getAdvertising();
  advertising->setMinInterval(0xA0);                     // 100 ms repeat interval: each seq is broadcast ~50 times per 5 s window, so scan-window misses on laptops still catch most seqs
  advertising->setMaxInterval(0xA0);
  advertiseFrame();                                      // first frame immediately so the gateway sees us within one period
}

void loop() {
  static uint32_t lastFrame = 0;
  pollSerial();
  if (millis() - lastFrame >= PERIOD_MS) {               // new reading strictly on the card's sampling period
    lastFrame = millis();
    advertiseFrame();
  }
  delay(20);                                             // light sleep would save power here; a rehearsal board on USB does not need it
}
