// fault_inject.cpp: serial console + per-type fault state.
// Console grammar (115200 baud, newline-terminated):
//   fault <type_id> stuck|offset|drop|none     e.g. "fault 1 stuck"
//   status                                     print battery + fault table
#include "fault_inject.h"
#include <Arduino.h>
#include "sim_config.h"
#include "power.h"

static FaultKind s_fault[256];             // per-type fault state, FAULT_NONE by default
static uint8_t   s_stuck[256][MAX_PAYLOAD_LEN];  // frozen payload per type for FAULT_STUCK
static uint8_t   s_stuck_len[256];
static bool      s_stuck_valid[256];
static bool (*s_extra)(const char *) = nullptr;  // module console extension (soil calibration etc.)

void fault_set_extra_console(bool (*handler)(const char *line)) {
    s_extra = handler;
}

void fault_init(void) {
    Serial.println("[sim] fault console ready: fault <type_id> stuck|offset|drop|none");
}

static void handle_line(char *line) {
    if (s_extra && s_extra(line)) return;  // module commands (e.g. "cal12 dry") get first refusal
    char cmd[16] = {0}, kind[16] = {0};
    int type_id = -1;
    if (sscanf(line, "%15s %d %15s", cmd, &type_id, kind) >= 1) {
        if (strcmp(cmd, "status") == 0) {                    // status: quick health dump for the instructor
            Serial.printf("[sim] battery=%umV low_batt=%d\n",
                          power_battery_mv(), power_low_batt());
            for (int t = 0; t < 256; t++)
                if (s_fault[t] != FAULT_NONE)
                    Serial.printf("[sim] fault active: type %d kind %d\n", t, s_fault[t]);
            return;
        }
        if (strcmp(cmd, "fault") == 0 && type_id >= 0 && type_id < 256) {
            FaultKind k = FAULT_NONE;
            if      (strcmp(kind, "stuck")  == 0) k = FAULT_STUCK;
            else if (strcmp(kind, "offset") == 0) k = FAULT_OFFSET;
            else if (strcmp(kind, "drop")   == 0) k = FAULT_DROP;
            s_fault[type_id] = k;
            s_stuck_valid[type_id] = false;                  // re-capture the frozen value on the next sample
            Serial.printf("[sim] fault on type %d set to %s\n", type_id, kind);
        }
    }
}

void fault_poll_serial(void) {
    static char buf[48];
    static uint8_t pos = 0;
    while (Serial.available()) {
        char c = Serial.read();
        if (c == '\n' || c == '\r') {
            if (pos) { buf[pos] = 0; handle_line(buf); pos = 0; }
        } else if (pos < sizeof(buf) - 1) {
            buf[pos++] = c;
        }
    }
}

FaultKind fault_get(uint8_t type_id) { return s_fault[type_id]; }

bool fault_apply(uint8_t type_id, uint8_t *payload, uint8_t *len,
                 uint8_t *status) {
    switch (s_fault[type_id]) {
    case FAULT_NONE:
        return true;
    case FAULT_DROP:
        return false;                                        // scheduler skips the advertisement: silent death, the liveness-watchdog lab
    case FAULT_STUCK:
        if (!s_stuck_valid[type_id]) {                       // freeze at the first sample after the command: looks maximally plausible
            memcpy(s_stuck[type_id], payload, *len);
            s_stuck_len[type_id] = *len;
            s_stuck_valid[type_id] = true;
        }
        memcpy(payload, s_stuck[type_id], s_stuck_len[type_id]);
        *len = s_stuck_len[type_id];
        *status |= STATUS_FAULT_INJECTED;                    // truth channel for instructor tooling only
        return true;
    case FAULT_OFFSET:
        // generic offset: perturb the first 16-bit field by +12.5% of full
        // scale; per-module offsets can override this in the module itself
        if (*len >= 2) {
            uint16_t v = payload[0] | (payload[1] << 8);
            v += 0x1000;                                     // fixed bias: visible against any plausibility band without saturating
            payload[0] = v & 0xFF;
            payload[1] = v >> 8;
        }
        *status |= STATUS_FAULT_INJECTED;
        return true;
    }
    return true;
}
