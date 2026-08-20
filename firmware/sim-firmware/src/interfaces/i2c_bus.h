// i2c_bus: shared Wire initialisation + raw register helpers for SIM2.
// One bus, three sensors (BME688, SCD41, VEML7700); modules must use these
// helpers rather than touching Wire directly so bus setup happens exactly once.
#pragma once
#include <stdint.h>
#ifdef ARDUINO
#include <Arduino.h>
#endif

void i2c_bus_init(void);                                     // idempotent: safe for every module's init() to call
bool i2c_probe(uint8_t addr);                                // presence check for selftest
bool i2c_write_cmd16(uint8_t addr, uint16_t cmd);            // Sensirion-style 16-bit command
bool i2c_read_words(uint8_t addr, uint8_t *buf, uint8_t n);  // raw read of n bytes
bool i2c_write_reg16(uint8_t addr, uint8_t reg, uint16_t value);  // VEML-style 16-bit LE register write
bool i2c_read_reg16(uint8_t addr, uint8_t reg, uint16_t *value);  // VEML-style 16-bit LE register read
uint8_t sensirion_crc8(const uint8_t *data, uint8_t len);    // CRC-8 (poly 0x31) guarding SCD41 words
