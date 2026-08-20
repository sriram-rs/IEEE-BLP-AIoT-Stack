// fault_inject: instructor-mode fault injection over the serial console.
// The frame carries STATUS_FAULT_INJECTED so instructor tooling knows the
// truth while the student's agent has to detect the lie from data alone.
#pragma once
#include <stdint.h>

enum FaultKind : uint8_t {
    FAULT_NONE = 0,
    FAULT_STUCK,     // payload frozen at the last honest sample
    FAULT_OFFSET,    // module-defined bias applied to the reading
    FAULT_DROP,      // frames for this sensor are simply not advertised
};

void fault_init(void);
void fault_poll_serial(void);              // parse pending console commands; call every loop
FaultKind fault_get(uint8_t type_id);

// Modules with their own console commands (e.g. soil calibration) register a
// handler; lines the fault console does not recognise are offered to it.
// Single owner of the serial buffer = no reader races.
void fault_set_extra_console(bool (*handler)(const char *line));

// Applied by the scheduler around each sample:
// returns false if the frame must be dropped entirely (FAULT_DROP).
bool fault_apply(uint8_t type_id, uint8_t *payload, uint8_t *len,
                 uint8_t *status);
