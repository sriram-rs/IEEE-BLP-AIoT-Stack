// pir_mod: type 3, SIM3, motion events.
// Payload (card 03): u8 motion, u16 event_count. 3 bytes.
#ifdef SENSOR_PIR
#include <Arduino.h>
#include "../../include/sensor_module.h"
#include "../../include/pins.h"
#include "../interfaces/gpio_event.h"

static int8_t s_ch = -1;

static bool pir_init(void) {
    s_ch = gpio_event_attach(PIN_PIR_OUT, false, 50);  // no pull-up (PIR drives its output); 50 ms debounce absorbs comparator chatter
    return s_ch >= 0;
}

static bool pir_sample(uint8_t *payload, uint8_t *len) {
    *len = 3;
    payload[0] = gpio_event_level(s_ch);               // current motion state; the card is explicit that this is motion, not presence
    put_u16(payload + 1, gpio_event_count(s_ch));      // cumulative events: lets the gateway compute activity even across lost frames
    return true;                                       // a level read cannot fail; a dead PIR shows as permanent zero, which the card's failure modes cover
}

extern const SensorModule MOD_PIR = {
    3, 1, 2000, "PIR",                                 // 2 s period: motion is the fast channel of the occupancy fusion
    pir_init, pir_sample,
};
#endif // SENSOR_PIR
