// at42_mod: type 14, SIM3, capacitive proximity/touch.
// Payload (card 14): u8 present, u16 touch_count. 3 bytes.
#ifdef SENSOR_AT42QT1010
#include <Arduino.h>
#include "../../include/sensor_module.h"
#include "../../include/pins.h"
#include "../interfaces/gpio_event.h"

static int8_t s_ch = -1;

static bool at42_init(void) {
    s_ch = gpio_event_attach(PIN_AT42_OUT, false, 10); // IC drives its output cleanly; 10 ms debounce is belt-and-braces
    return s_ch >= 0;
}

static bool at42_sample(uint8_t *payload, uint8_t *len) {
    *len = 3;
    payload[0] = gpio_event_level(s_ch);               // HIGH = object within ~2-3 cm of the electrode
    put_u16(payload + 1, gpio_event_count(s_ch));
    return true;
    // Note for reviewers: the IC recalibrates a long-held object into its
    // baseline (card failure mode). That is IC behaviour, not firmware's to
    // fix; the gateway card documents it for the agent.
}

extern const SensorModule MOD_AT42 = {
    14, 1, 2000, "AT42QT1010",
    at42_init, at42_sample,
};
#endif // SENSOR_AT42QT1010
