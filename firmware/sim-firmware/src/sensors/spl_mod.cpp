// spl_mod: type 8, SIM4, sound level from the envelope detector.
// Payload (card 08): u16 spl_db*10. 2 bytes.
// Privacy by hardware: only the envelope DC level ever reaches this code;
// no waveform exists to leak.
#ifdef SENSOR_SPL
#include <Arduino.h>
#include "../../include/sensor_module.h"
#include "../../include/pins.h"
#include "../interfaces/adc_in.h"

// Single-point calibration: dB = SLOPE * mv + OFFSET. These defaults are
// board-bringup placeholders; the acceptance procedure (known source at
// known distance) writes real values, stored here until per-unit NVS
// calibration is added by the firmware team.
#define CAL_SLOPE_DB_PER_MV 0.030f
#define CAL_OFFSET_DB       30.0f

static bool spl_init(void) {
    adc_in_init(PIN_ADC_SPL);
    return true;                         // envelope output is always a valid voltage; a dead mic reads the floor, which the card flags as a failure mode
}

static bool spl_sample(uint8_t *payload, uint8_t *len) {
    *len = 2;
    uint16_t mv = adc_read_mv(PIN_ADC_SPL, 4);      // 16x oversample: envelope moves slowly by design
    float db = CAL_SLOPE_DB_PER_MV * mv + CAL_OFFSET_DB;
    if (db < 25.0f)  db = 25.0f;                    // clamp to the card's plausibility floor: below this is electronics noise, not sound
    if (db > 125.0f) db = 125.0f;
    put_u16(payload, (uint16_t)(db * 10.0f));
    return true;
}

extern const SensorModule MOD_SPL = {
    8, 1, 2000, "SPL",                              // 2 s: the zero-latency channel in occupancy fusion
    spl_init, spl_sample,
};
#endif // SENSOR_SPL
