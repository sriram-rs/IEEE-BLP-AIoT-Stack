// jsn_mod: type 9, SIM4, ultrasonic distance via pulse capture.
// Payload (card 09): u16 distance_mm. 2 bytes.
// Architecture note honoured: this sensor is NOT analog; it lives on SIM4
// only because the connector carries two GPIO lines (PIN_JSN_TRIG/ECHO).
#ifdef SENSOR_JSN_SR04T
#include <Arduino.h>
#include "../../include/sensor_module.h"
#include "../../include/pins.h"
#include "../interfaces/pulse_capture.h"

#define ECHO_TIMEOUT_US 30000            // 30 ms > max echo at 4.5 m (~26 ms): anything longer is "no echo"

static bool jsn_init(void) {
    pulse_capture_init(PIN_JSN_TRIG, PIN_JSN_ECHO);
    return true;                         // no presence probe exists; the first sample's timeout is the health check
}

static bool jsn_sample(uint8_t *payload, uint8_t *len) {
    *len = 2;
    uint32_t us = pulse_capture_measure_us(ECHO_TIMEOUT_US);
    if (us == 0) {                       // timeout: soft target, out of range, or dead transducer
        put_u16(payload, 0);             // 0 mm is impossible (200 mm blind zone), so it can never be mistaken for a reading
        return false;                    // "no echo" is a status, never a distance (card failure mode, verbatim)
    }
    // distance = us * c / 2; 343 m/s at 20 C baked in here. The TEMPERATURE
    // CORRECTION IS DELIBERATELY NOT DONE ON THE SIM: the gateway/agent owns
    // it (One Sensor Corrects Another), pairing this with a DS18B20 card.
    uint32_t mm = us * 343UL / 2000UL;
    if (mm < 200 || mm > 4700) {         // outside the physical envelope on the card: blind zone or ghost echo
        put_u16(payload, (uint16_t)mm);  // report what was measured, flagged bad, so students can see ghost echoes in the data
        return false;
    }
    put_u16(payload, (uint16_t)mm);
    return true;
}

extern const SensorModule MOD_JSN = {
    9, 1, 5000, "JSN-SR04T",
    jsn_init, jsn_sample,
};
#endif // SENSOR_JSN_SR04T
