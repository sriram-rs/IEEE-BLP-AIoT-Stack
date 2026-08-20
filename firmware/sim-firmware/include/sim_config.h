// sim_config.h: identity, frame constants, and timing shared by all modules.
// Values that mirror the gateway (gateway/core.py) are marked CONTRACT: they
// must never change on one side only.
#pragma once
#include <stdint.h>

#ifndef KIT_ID
#define KIT_ID 1                       // which kit this SIM belongs to; set per assembled kit in platformio.ini
#endif
#ifndef SIM_VARIANT
#error "Build with -DSIM_VARIANT=1..5 (use a platformio.ini environment)"
#endif

// CONTRACT constants: identical values live in gateway/core.py
#define COMPANY_ID              0xFFFF // development BLE company ID the gateway filters on
#define STATUS_SENSOR_OK        0x01
#define STATUS_LOW_BATT         0x02
#define STATUS_FAULT_INJECTED   0x04
#define MAX_PAYLOAD_LEN         12     // CONTRACT: header(11) + payload(<=12) + company(2) fits the 31-byte legacy adv budget

#define ADV_REPEAT_INTERVAL_UNITS 0xA0 // 100 ms adv repeat: ~50 copies of each seq per 5 s period survive laptop scan windows
#define SEQ_PERSIST_EVERY       64     // write seq to NVS every 64 increments: bounds flash wear to ~1 write/5 min at 5 s periods
#define LOW_BATT_MV             3300   // below this battery voltage the low_batt status bit is set
#define SELFTEST_RETRIES        3      // boot-time presence probes per sensor before declaring it absent
