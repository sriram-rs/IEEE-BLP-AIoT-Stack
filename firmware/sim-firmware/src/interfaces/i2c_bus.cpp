// i2c_bus.cpp: Wire wrapper for the SIM2 shared bus.
#include "i2c_bus.h"
#include <Wire.h>
#include "pins.h"

#if SIM_VARIANT == 2                     // whole file only meaningful on the I2C SIM

static bool s_inited = false;

void i2c_bus_init(void) {
    if (s_inited) return;                // idempotent: three modules call this, the bus starts once
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL, 100000);  // 100 kHz: every sensor on this SIM supports it and it tolerates long harness wiring better than 400 kHz
    s_inited = true;
}

bool i2c_probe(uint8_t addr) {
    Wire.beginTransmission(addr);
    return Wire.endTransmission() == 0;  // ACK on the address byte = device present
}

bool i2c_write_cmd16(uint8_t addr, uint16_t cmd) {
    Wire.beginTransmission(addr);
    Wire.write(cmd >> 8);                // Sensirion commands go MSB first on the wire
    Wire.write(cmd & 0xFF);
    return Wire.endTransmission() == 0;
}

bool i2c_read_words(uint8_t addr, uint8_t *buf, uint8_t n) {
    if (Wire.requestFrom((int)addr, (int)n) != n) return false;  // short read = failed acquisition, caller flags sensor_ok
    for (uint8_t i = 0; i < n; i++) buf[i] = Wire.read();
    return true;
}

bool i2c_write_reg16(uint8_t addr, uint8_t reg, uint16_t value) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(value & 0xFF);            // VEML7700 registers are little-endian, unlike Sensirion
    Wire.write(value >> 8);
    return Wire.endTransmission() == 0;
}

bool i2c_read_reg16(uint8_t addr, uint8_t reg, uint16_t *value) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) return false;   // repeated start, no stop: required by the VEML7700 read protocol
    if (Wire.requestFrom((int)addr, 2) != 2) return false;
    *value = Wire.read() | (Wire.read() << 8);
    return true;
}

uint8_t sensirion_crc8(const uint8_t *data, uint8_t len) {
    uint8_t crc = 0xFF;                  // init value per Sensirion datasheets
    for (uint8_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t b = 0; b < 8; b++)
            crc = (crc & 0x80) ? (crc << 1) ^ 0x31 : (crc << 1);  // polynomial 0x31
    }
    return crc;
}

#endif // SIM_VARIANT == 2
