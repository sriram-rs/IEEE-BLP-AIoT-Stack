// scd41_mod: type 6, SIM2, CO2 via raw I2C (no vendor library needed).
// Payload (card 06): u16 co2_ppm, int16 t*100, u16 rh*100. 6 bytes.
#ifdef SENSOR_SCD41
#include <Arduino.h>
#include "../../include/sensor_module.h"
#include "../interfaces/i2c_bus.h"

#define SCD41_ADDR 0x62
#define CMD_START_PERIODIC 0x21B1        // 5 s measurement interval, the card's sampling period
#define CMD_READ_MEASUREMENT 0xEC05
#define CMD_DATA_READY 0xE4B8

static bool scd_init(void) {
    i2c_bus_init();
    if (!i2c_probe(SCD41_ADDR)) return false;
    i2c_write_cmd16(SCD41_ADDR, CMD_START_PERIODIC);  // sensor free-runs; we harvest whatever is ready at our cadence
    return true;
}

static bool word_ok(const uint8_t *p) {
    return sensirion_crc8(p, 2) == p[2];  // every 16-bit word carries its own CRC on this part
}

static bool scd_sample(uint8_t *payload, uint8_t *len) {
    *len = 6;
    uint8_t buf[9];
    if (!i2c_write_cmd16(SCD41_ADDR, CMD_DATA_READY)) return false;
    delay(1);
    if (!i2c_read_words(SCD41_ADDR, buf, 3) || !word_ok(buf)) return false;
    if (((buf[0] << 8 | buf[1]) & 0x07FF) == 0) return false;   // data-ready bits clear: no fresh measurement, report fault rather than resend stale
    if (!i2c_write_cmd16(SCD41_ADDR, CMD_READ_MEASUREMENT)) return false;
    delay(1);
    if (!i2c_read_words(SCD41_ADDR, buf, 9)) return false;
    if (!word_ok(buf) || !word_ok(buf + 3) || !word_ok(buf + 6)) return false;  // any bad CRC invalidates the whole read

    uint16_t co2 = buf[0] << 8 | buf[1];
    // datasheet conversions: T = -45 + 175*raw/65535, RH = 100*raw/65535
    float t  = -45.0f + 175.0f * (buf[3] << 8 | buf[4]) / 65535.0f;
    float rh = 100.0f * (buf[6] << 8 | buf[7]) / 65535.0f;

    put_u16(payload, co2);
    put_i16(payload + 2, (int16_t)(t * 100));
    put_u16(payload + 4, (uint16_t)(rh * 100));
    return true;
}

extern const SensorModule MOD_SCD41 = {
    6, 1, 5000, "SCD41",
    scd_init, scd_sample,
};
#endif // SENSOR_SCD41
