// water_mod: type 13, SIM4, bare-trace water presence.
// Payload (card 13): u8 wet, u16 raw_mv. 3 bytes.
#ifdef SENSOR_WATER_TRACE
#include <Arduino.h>
#include "../../include/sensor_module.h"
#include "../../include/pins.h"
#include "../interfaces/adc_in.h"

#define WET_THRESHOLD_MV 1500            // below this the traces are bridged; dry reads near the excitation rail (~3100 mV)

static bool water_init(void) {
    adc_in_init(PIN_ADC_WATER);
    pinMode(PIN_WATER_EXCITE, OUTPUT);
    digitalWrite(PIN_WATER_EXCITE, LOW); // traces unpowered between samples: the anti-electrolysis rule from the card, in hardware
    return true;
}

static bool water_sample(uint8_t *payload, uint8_t *len) {
    *len = 3;
    digitalWrite(PIN_WATER_EXCITE, HIGH);            // energise only for the measurement window
    delay(5);                                        // RC settle on the trace + pull-up network
    uint16_t mv = adc_read_mv(PIN_ADC_WATER, 4);
    digitalWrite(PIN_WATER_EXCITE, LOW);             // total excitation ~6 ms per 5 s = 0.1% duty: trace corrosion negligible over a semester
    payload[0] = (mv < WET_THRESHOLD_MV) ? 1 : 0;
    put_u16(payload + 1, mv);                        // raw level lets the gateway watch the dry-baseline drift failure mode
    return true;
}

extern const SensorModule MOD_WATER = {
    13, 1, 5000, "WATER-TRACE",
    water_init, water_sample,
};
#endif // SENSOR_WATER_TRACE
