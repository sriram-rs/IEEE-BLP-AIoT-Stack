// modbus_rtu: minimal Modbus RTU master for SIM5 (function 0x03 only).
// Self-contained: no library dependency, ~100 lines, reviewable in one pass.
// The SIM is always the bus master; sensors (energy meter, soil probe) are slaves.
#pragma once
#include <stdint.h>

void modbus_init(uint32_t baud);
// Read n holding registers starting at reg from slave addr into words[].
// Returns true on a CRC-valid, correctly-sized response. A false return is a
// communications fault: the caller clears sensor_ok and never fabricates values.
bool modbus_read_holding(uint8_t addr, uint16_t reg, uint16_t n, uint16_t *words);
