// adv_builder: packs the CONTRACT frame and owns the BLE advertising handle.
#pragma once
#include <stdint.h>

// Initialise BLE once at boot (empty device name keeps the adv small).
void adv_init(void);

// Pack header + payload into Manufacturer Specific Data and start/refresh the
// advertisement. seq and tick are supplied by the scheduler so this module
// stays stateless about time.
void adv_publish(uint8_t type_id, uint8_t schema, uint16_t seq,
                 uint32_t tick_ms, uint8_t status,
                 const uint8_t *payload, uint8_t len);
