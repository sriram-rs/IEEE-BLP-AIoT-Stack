// seq_store: per-sensor sequence counters that survive reboots via NVS.
// Persistence matters: a counter restarting at 0 after a battery swap would
// look like 65k lost packets to the gateway's delivery-ratio accounting.
#pragma once
#include <stdint.h>

void seq_store_init(void);
uint16_t seq_next(uint8_t type_id);   // increment-and-return; persists every SEQ_PERSIST_EVERY increments
void seq_flush(void);                 // force-persist all counters (called before intentional resets)
