// main.cpp: boot, selftest, and the sample -> fault -> advertise scheduler.
// Design rules enforced here (from the architecture document):
//   1. The SIM measures, it never interprets: no thresholds except self-protection.
//   2. Everything that can fail sets a status bit: a failed sample still
//      advertises, flagged not-ok; silent garbage is designed out.
//   3. Fault injection is a first-class feature with its own truth bit.
#include <Arduino.h>
#include "../include/sim_config.h"
#include "../include/sensor_module.h"
#include "common/adv_builder.h"
#include "common/seq_store.h"
#include "common/power.h"
#include "common/fault_inject.h"

#ifdef SENSOR_SEN0193
extern bool sen0193_console(const char *line);   // calibration console hook; forwarded below
#endif

static const SensorModule **s_mods;
static uint8_t  s_count;
static uint32_t s_next_due[16];                  // per-module next sample time; 16 covers the largest variant with headroom
static bool     s_present[16];                   // selftest result per module

void setup() {
    Serial.begin(115200);
    Serial.printf("\n[sim] SIM%d firmware, kit %d\n", SIM_VARIANT, KIT_ID);

    power_init();
    seq_store_init();
    adv_init();
    fault_init();
#ifdef SENSOR_SEN0193
    fault_set_extra_console(sen0193_console);    // soil calibration commands share the single serial reader
#endif

    s_mods = sensor_registry(&s_count);
    for (uint8_t i = 0; i < s_count; i++) {
        // boot selftest with retries: transient bus glitches at power-up must
        // not condemn a healthy sensor for the whole session
        bool ok = false;
        for (uint8_t r = 0; r < SELFTEST_RETRIES && !ok; r++) {
            ok = s_mods[i]->init();
            if (!ok) delay(100);
        }
        s_present[i] = ok;
        Serial.printf("[sim] selftest %-12s type=%u -> %s\n",
                      s_mods[i]->name, s_mods[i]->type_id, ok ? "OK" : "ABSENT/FAULT");
        // stagger start times so multi-sensor SIMs rotate advertisements
        // instead of bursting them into the same scan window
        s_next_due[i] = millis() + (i * 700);
    }
}

void loop() {
    fault_poll_serial();

    for (uint8_t i = 0; i < s_count; i++) {
        if ((int32_t)(millis() - s_next_due[i]) < 0) continue;   // signed comparison survives millis() wrap at 49 days
        const SensorModule *m = s_mods[i];
        s_next_due[i] += m->period_ms;                           // schedule from the previous due time, not "now": no cadence drift

        uint8_t payload[MAX_PAYLOAD_LEN];
        uint8_t len = 0;
        uint8_t status = 0;

        bool ok = s_present[i] && m->sample(payload, &len);      // an absent sensor never gets sampled, but still advertises below
        if (ok) status |= STATUS_SENSOR_OK;                      // rule 2: ok is earned per sample, never assumed
        if (power_low_batt()) status |= STATUS_LOW_BATT;

        if (!fault_apply(m->type_id, payload, &len, &status))    // rule 3: instructor faults transform or drop the frame here
            continue;                                            // FAULT_DROP: the liveness-watchdog lab sees this sensor go silent

        uint16_t seq = seq_next(m->type_id);                     // one seq per reading; radio repeats reuse it and the gateway dedupes
        adv_publish(m->type_id, m->schema_version, seq, millis(), status, payload, len);

        Serial.printf("[sim] adv type=%u seq=%u len=%u status=0x%02X\n",
                      m->type_id, seq, len, status);
    }

    delay(10);                                                   // 10 ms tick: fine-grained enough for 2 s periods, negligible power cost on a power bank
}
