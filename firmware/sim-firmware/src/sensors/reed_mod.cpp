// reed_mod: type 10, SIM3, door/window contact.
// Payload (card 10): u8 door_open, u16 transition_count. 3 bytes.
#ifdef SENSOR_REED
#include <Arduino.h>
#include "../../include/sensor_module.h"
#include "../../include/pins.h"
#include "../interfaces/gpio_event.h"

static int8_t s_ch = -1;

static bool reed_init(void) {
    s_ch = gpio_event_attach(PIN_REED_IN, true, 20);   // pull-up: switch shorts to GND when the magnet closes it; 20 ms kills contact bounce
    return s_ch >= 0;
}

static bool reed_sample(uint8_t *payload, uint8_t *len) {
    *len = 3;
    payload[0] = gpio_event_level(s_ch);               // with the pull-up, HIGH = circuit open = door open (magnet away)
    put_u16(payload + 1, gpio_event_count(s_ch));      // transition count survives between frames: no door event is lost to packet loss
    return true;
}

extern const SensorModule MOD_REED = {
    10, 1, 2000, "REED",
    reed_init, reed_sample,
};
#endif // SENSOR_REED
