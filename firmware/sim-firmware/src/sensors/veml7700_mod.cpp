// veml7700_mod: type 7, SIM2, illuminance via raw I2C registers.
// Payload (card 07): u32 lux * 100. 4 bytes.
#ifdef SENSOR_VEML7700
#include <Arduino.h>
#include "../../include/sensor_module.h"
#include "../interfaces/i2c_bus.h"

#define VEML_ADDR 0x10
#define REG_ALS_CONF 0x00
#define REG_ALS_DATA 0x04

// Fixed configuration: gain 1/8, integration 100 ms. One setting covering
// bright daylight without saturating; the resolution constant below is the
// datasheet lux-per-count for exactly this configuration. Auto-ranging for
// moonlight-level readings is a documented extension for the firmware team.
#define ALS_CONF_VALUE 0x1000            // gain 1/8 (bits 12:11 = 10), IT 100 ms (bits 9:6 = 0000), power on
#define LUX_PER_COUNT 0.4608f            // datasheet resolution at gain 1/8, IT 100 ms

static bool veml_init(void) {
    i2c_bus_init();
    if (!i2c_probe(VEML_ADDR)) return false;
    return i2c_write_reg16(VEML_ADDR, REG_ALS_CONF, ALS_CONF_VALUE);
}

static bool veml_sample(uint8_t *payload, uint8_t *len) {
    *len = 4;
    uint16_t raw;
    if (!i2c_read_reg16(VEML_ADDR, REG_ALS_DATA, &raw)) return false;
    float lux = raw * LUX_PER_COUNT;
    // High-lux nonlinearity correction from the Vishay app note: mandatory
    // above ~1000 counts at this gain, harmless below
    if (lux > 1000.0f)
        lux = (((6.0135e-13f * lux - 9.3924e-9f) * lux + 8.1488e-5f) * lux + 1.0023f) * lux;
    put_u32(payload, (uint32_t)(lux * 100.0f));
    return true;
}

extern const SensorModule MOD_VEML7700 = {
    7, 1, 5000, "VEML7700",
    veml_init, veml_sample,
};
#endif // SENSOR_VEML7700
