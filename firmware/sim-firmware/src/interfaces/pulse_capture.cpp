// pulse_capture.cpp: blocking single-shot echo timing.
// Blocking is acceptable: one measurement is ~26 ms worst case at 4.5 m and
// the scheduler runs one sensor at a time on SIM4.
#include "pulse_capture.h"
#include <Arduino.h>

static uint8_t s_trig, s_echo;

void pulse_capture_init(uint8_t trig_pin, uint8_t echo_pin) {
    s_trig = trig_pin;
    s_echo = echo_pin;
    pinMode(s_trig, OUTPUT);
    digitalWrite(s_trig, LOW);
    pinMode(s_echo, INPUT);
}

uint32_t pulse_capture_measure_us(uint32_t timeout_us) {
    digitalWrite(s_trig, HIGH);
    delayMicroseconds(10);                 // JSN-SR04T datasheet: >=10 us trigger pulse starts a measurement
    digitalWrite(s_trig, LOW);
    // pulseIn handles both edge waits with its own timeout; returns 0 on
    // timeout which we pass through as the explicit "no echo" signal
    return pulseIn(s_echo, HIGH, timeout_us);
}
