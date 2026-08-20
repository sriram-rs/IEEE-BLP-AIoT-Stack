// sen0193_mod: type 12, SIM4, capacitive soil moisture with NVS calibration.
// Payload (card 12): u16 raw_mv, u16 moisture_pct*10. 4 bytes.
// Calibration console (the agent-guided dialogue lands here):
//   cal12 dry    capture current reading as the dry-air anchor
//   cal12 wet    capture current reading as the saturated anchor
#ifdef SENSOR_SEN0193
#include <Arduino.h>
#include <Preferences.h>
#include "../../include/sensor_module.h"
#include "../../include/pins.h"
#include "../interfaces/adc_in.h"

static Preferences s_cal;
static uint16_t s_dry_mv = 0, s_wet_mv = 0;   // 0 = anchor not set: percentages are withheld until both exist

static bool soil_init(void) {
    adc_in_init(PIN_ADC_SEN0193);
    s_cal.begin("soilcal", false);            // anchors live per PROBE in this SIM's NVS; card mirrors them for the agent
    s_dry_mv = s_cal.getUShort("dry", 0);
    s_wet_mv = s_cal.getUShort("wet", 0);
    return true;
}

// Console hook called from fault_inject's serial loop via weak linkage would
// couple modules; instead main.cpp forwards unrecognised lines here.
bool sen0193_console(const char *line) {
    uint16_t mv = adc_read_mv(PIN_ADC_SEN0193, 5);
    if (strcmp(line, "cal12 dry") == 0) {
        s_dry_mv = mv;
        s_cal.putUShort("dry", mv);           // persisted immediately: a calibration lost to a power cycle poisons a whole deployment
        Serial.printf("[sim] soil dry anchor = %u mV\n", mv);
        return true;
    }
    if (strcmp(line, "cal12 wet") == 0) {
        s_wet_mv = mv;
        s_cal.putUShort("wet", mv);
        Serial.printf("[sim] soil wet anchor = %u mV\n", mv);
        return true;
    }
    return false;
}

static bool soil_sample(uint8_t *payload, uint8_t *len) {
    *len = 4;
    uint16_t mv = adc_read_mv(PIN_ADC_SEN0193, 5);
    put_u16(payload, mv);                     // raw always reported: No Meaning Without Calibration works both ways
    if (s_dry_mv == 0 || s_wet_mv == 0 || s_dry_mv <= s_wet_mv) {  // uncalibrated, or anchors nonsensical (dry must read higher than wet)
        put_u16(payload + 2, 0);
        return false;                         // sensor_ok false: an uncalibrated percentage would be a fabricated number
    }
    float pct = 100.0f * (s_dry_mv - mv) / (float)(s_dry_mv - s_wet_mv);  // linear between the two anchors, wetter = lower voltage
    if (pct < 0.0f)   pct = 0.0f;             // clamp: probe in air drier than the dry anchor, or wetter than saturation
    if (pct > 100.0f) pct = 100.0f;
    put_u16(payload + 2, (uint16_t)(pct * 10.0f));
    return true;
}

extern const SensorModule MOD_SEN0193 = {
    12, 1, 10000, "SEN0193",                  // 10 s: soil moisture moves on minutes-to-hours timescales
    soil_init, soil_sample,
};
#endif // SENSOR_SEN0193
