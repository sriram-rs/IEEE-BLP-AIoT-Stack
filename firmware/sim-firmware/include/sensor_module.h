// sensor_module.h: the contract every sensor module implements.
// A module is a self-contained .cpp exporting one SensorModule struct; the
// registry collects the enabled ones and main.cpp schedules them. Nothing
// outside a module knows how its sensor works; nothing inside a module knows
// about BLE, scheduling, or fault injection.
#pragma once
#include <stdint.h>
#include "sim_config.h"

struct SensorModule {
    uint8_t  type_id;          // CONTRACT: sensor_type_id resolving the gateway card
    uint8_t  schema_version;   // CONTRACT: payload layout version on that card
    uint32_t period_ms;        // sampling cadence; mirror the card's sampling_period_s
    const char *name;          // for serial logs and the selftest report

    // One-time hardware init and presence check. Return false if the sensor
    // is absent or failing: the scheduler will still advertise frames for it
    // with sensor_ok cleared, so the gateway sees an explicit fault, never
    // silence it cannot interpret.
    bool (*init)(void);

    // Fill payload (<= MAX_PAYLOAD_LEN bytes, layout per the sensor card) and
    // set *len. Return false on a failed acquisition (CRC error, timeout,
    // rail fault): the frame still goes out, flagged not-ok. Rule: a module
    // never fabricates a plausible number for a failed read.
    bool (*sample)(uint8_t *payload, uint8_t *len);
};

// Implemented by sensors/sensor_registry.cpp from the -DSENSOR_* build flags.
const SensorModule **sensor_registry(uint8_t *count);

// Little-endian packing helpers shared by every module (CONTRACT byte order).
static inline void put_u16(uint8_t *p, uint16_t v) { p[0] = v & 0xFF; p[1] = v >> 8; }
static inline void put_i16(uint8_t *p, int16_t v)  { put_u16(p, (uint16_t)v); }
static inline void put_u32(uint8_t *p, uint32_t v) { put_u16(p, v & 0xFFFF); put_u16(p + 2, v >> 16); }
