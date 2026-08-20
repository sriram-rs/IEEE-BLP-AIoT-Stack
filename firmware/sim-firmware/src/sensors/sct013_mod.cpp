// sct013_mod: type 11, SIM4, AC current via clamp CT.
// Payload (card 11): u16 irms_a*1000, u16 apparent_va. 4 bytes.
#ifdef SENSOR_SCT013
#include <Arduino.h>
#include "../../include/sensor_module.h"
#include "../../include/pins.h"
#include "../interfaces/adc_in.h"

#define CT_MV_PER_A   33.3f              // SCT-013-030 transfer: 30 A -> 1 V; ONLY burden-resistor variants are supported (safety, per the card)
#define MAINS_V_NOM   230.0f             // apparent power assumes nominal mains; the card documents this approximation
#define N_SAMPLES     1024               // ~1 s of sampling at ~1 kHz: >= 50 mains cycles for a stable RMS
#define SAMPLE_US     950                // ~1.05 kHz effective rate including ADC conversion time

static bool sct_init(void) {
    adc_in_init(PIN_ADC_SCT013);
    return true;                         // a clamp cannot be probed; the kettle acceptance test on the card is the real install check
}

static bool sct_sample(uint8_t *payload, uint8_t *len) {
    *len = 4;
    uint16_t rms_mv = adc_read_rms_mv(PIN_ADC_SCT013, N_SAMPLES, SAMPLE_US);  // AC RMS around the bias point, DC removed in the interface layer
    float irms = rms_mv / CT_MV_PER_A;
    if (irms < 0.024f) irms = 0.0f;      // below the card's ~24 mA unassisted floor: report clean zero, not ADC noise dressed as milliamps
    float va = MAINS_V_NOM * irms;
    put_u16(payload, (uint16_t)(irms * 1000.0f));
    put_u16(payload + 2, (uint16_t)va);
    return true;
}

extern const SensorModule MOD_SCT013 = {
    11, 1, 2000, "SCT-013",
    sct_init, sct_sample,
};
#endif // SENSOR_SCT013
