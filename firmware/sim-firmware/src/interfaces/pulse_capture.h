// pulse_capture: trigger/echo time-of-flight measurement for the JSN-SR04T.
// This lives in interfaces/, not the sensor module, because it is the honest
// implementation of the "SIM4 is not really analog for this sensor" note in
// the architecture: the measurement is GPIO interrupt timing, not ADC.
#pragma once
#include <stdint.h>

void pulse_capture_init(uint8_t trig_pin, uint8_t echo_pin);
// Fire one trigger and time the echo. Returns echo width in microseconds,
// or 0 on timeout (no echo = status, never a distance).
uint32_t pulse_capture_measure_us(uint32_t timeout_us);
