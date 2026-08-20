// analog420_mod: type 4, SIM4, generic 4-20 mA transmitter (anemometer default).
// Payload (card 04): u16 loop_ma*100, int16 value*100 (wind m/s for the
// default transmitter config). 4 bytes.
#ifdef SENSOR_ANALOG_420MA
#include <Arduino.h>
#include "../../include/sensor_module.h"
#include "../../include/pins.h"
#include "../interfaces/adc_in.h"

// Transmitter range mapping: change these two for a different 4-20 mA
// instrument (level, pressure...); the loop electronics stay identical.
#define RANGE_LO 0.0f                    // engineering value at 4 mA
#define RANGE_HI 30.0f                   // engineering value at 20 mA (anemometer: 30 m/s)

static bool a420_init(void) {
    adc_in_init(PIN_ADC_420MA);
    return true;                         // a current loop has no probe-able presence; live-zero does the health check every sample
}

static bool a420_sample(uint8_t *payload, uint8_t *len) {
    *len = 4;
    uint16_t mv = adc_read_mv(PIN_ADC_420MA, 5);              // 32x oversample: loop signals are slow, noise floor matters more than speed
    float ma = (float)mv / R_BURDEN_420MA_OHM;                // Ohm's law across the burden resistor
    put_u16(payload, (uint16_t)(ma * 100.0f));                // raw loop current always reported: the gateway's fault semantics read it
    if (ma < 3.8f || ma > 20.5f) {                            // live-zero violated: broken loop or transmitter fault, thresholds from the card
        put_i16(payload + 2, 0);                              // mapped value zeroed, and:
        return false;                                         // sensor_ok cleared: out-of-band current is a fault, never a reading
    }
    float value = RANGE_LO + (ma - 4.0f) / 16.0f * (RANGE_HI - RANGE_LO);  // linear 4-20 mA -> engineering units
    put_i16(payload + 2, (int16_t)(value * 100.0f));
    return true;
}

extern const SensorModule MOD_ANALOG420 = {
    4, 1, 5000, "4-20mA",
    a420_init, a420_sample,
};
#endif // SENSOR_ANALOG_420MA
