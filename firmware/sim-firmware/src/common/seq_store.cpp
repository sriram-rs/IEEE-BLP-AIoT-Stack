// seq_store.cpp: NVS-backed counters, one per sensor type on this SIM.
#include "seq_store.h"
#include <Preferences.h>
#include "sim_config.h"

static Preferences s_prefs;
static uint16_t s_seq[256];           // indexed by type_id; 512 bytes of RAM buys O(1) lookup with no map code
static uint16_t s_since_persist[256]; // increments since last NVS write, per type

void seq_store_init(void) {
    s_prefs.begin("simseq", false);   // dedicated NVS namespace so a factory reset can wipe it selectively
    for (int t = 0; t < 256; t++) {
        char key[8];
        snprintf(key, sizeof(key), "s%d", t);
        // resume slightly ahead of the persisted value: increments since the
        // last flush were lost, so jumping forward guarantees the gateway
        // never sees a seq go backwards (backwards = phantom 65k loss)
        s_seq[t] = s_prefs.getUShort(key, 0) + SEQ_PERSIST_EVERY;
    }
}

uint16_t seq_next(uint8_t type_id) {
    s_seq[type_id]++;                 // natural u16 wrap at 65535 matches the gateway's modular gap math
    if (++s_since_persist[type_id] >= SEQ_PERSIST_EVERY) {  // batch writes: NVS flash endurance is finite
        s_since_persist[type_id] = 0;
        char key[8];
        snprintf(key, sizeof(key), "s%d", type_id);
        s_prefs.putUShort(key, s_seq[type_id]);
    }
    return s_seq[type_id];
}

void seq_flush(void) {
    for (int t = 0; t < 256; t++) {
        if (s_since_persist[t] == 0) continue;   // skip untouched counters: avoids 250+ pointless flash writes
        char key[8];
        snprintf(key, sizeof(key), "s%d", t);
        s_prefs.putUShort(key, s_seq[t]);
        s_since_persist[t] = 0;
    }
}
