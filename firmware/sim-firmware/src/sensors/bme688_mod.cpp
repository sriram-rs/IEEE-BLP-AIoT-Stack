// bme688_mod: type 2, SIM2, air quality.
// Payload (card 02): int16 t*100, u16 rh*100, u16 p_hPa*10, u16 iaq*10,
//                    u16 eco2_ppm, u16 bvoc*100. 12 bytes (the payload budget).
//
// HANDOVER NOTE (firmware team, read this first): real IAQ/eCO2/bVOC come
// from Bosch's proprietary BSEC2 library, which cannot be redistributed in
// this repo. This module compiles and runs WITHOUT it: T/RH/P read via raw
// I2C from the BME688's compensation-free quick path is NOT implemented here
// (full raw compensation is ~300 lines of vendor constants); instead, until
// BSEC is integrated, this module reports sensor-present with sensor_ok
// FALSE and zeroed fields, which the gateway interprets correctly as "sensor
// alive, data not trustworthy yet". Integration steps:
//   1. Add BSEC2 to platformio.ini lib_deps (Bosch licence acknowledged).
//   2. Replace bme_sample() below with the BSEC output loop.
//   3. Keep the payload layout EXACTLY as the card specifies.
// This is honest scaffolding, not a fake sensor: the alternative (synthetic
// plausible values) would violate the firmware's first design rule.
#ifdef SENSOR_BME688
#include <Arduino.h>
#include "../../include/sensor_module.h"
#include "../interfaces/i2c_bus.h"

#define BME_ADDR 0x76                    // SDO pulled low on the packaged sensor per the Rev5 schematic
#define REG_CHIP_ID 0xD0
#define CHIP_ID_BME688 0x61

static bool bme_init(void) {
    i2c_bus_init();
    if (!i2c_probe(BME_ADDR)) return false;
    // chip-ID check: presence AND identity, so a mis-strapped part on the
    // same address cannot masquerade as a BME688
    uint16_t v;
    if (!i2c_read_reg16(BME_ADDR, REG_CHIP_ID, &v)) return false;
    return (v & 0xFF) == CHIP_ID_BME688;  // register is one byte; the 16-bit helper reads it plus the next
}

static bool bme_sample(uint8_t *payload, uint8_t *len) {
    *len = 12;
    memset(payload, 0, 12);              // zeroed fields + sensor_ok false = "present, awaiting BSEC integration"
    return false;                        // deliberately not-ok until BSEC lands; see the handover note above
}

extern const SensorModule MOD_BME688 = {
    2, 1, 5000, "BME688",
    bme_init, bme_sample,
};
#endif // SENSOR_BME688
