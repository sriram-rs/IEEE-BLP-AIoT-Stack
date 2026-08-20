// power.cpp: rail switching and battery measurement.
// Deliberate design note: this firmware does NOT deep-sleep. Kits run from
// power banks, and most power banks cut output below ~50-60 mA average draw;
// a deep-sleeping SIM would have its supply killed mid-deployment. Continuous
// advertising doubles as the keep-alive load.
#include "power.h"
#include <Arduino.h>
#include "pins.h"
#include "sim_config.h"

void power_init(void) {
    pinMode(PIN_SENSOR_RAIL_EN, OUTPUT);
    digitalWrite(PIN_SENSOR_RAIL_EN, HIGH);   // sensors powered by default from boot
    analogSetPinAttenuation(PIN_BATT_SENSE, ADC_11db);  // 11 dB attenuation reads up to ~3.1 V linearly on the divider node
}

void power_rail(bool on) {
    digitalWrite(PIN_SENSOR_RAIL_EN, on ? HIGH : LOW);
    if (on) delay(50);                        // settle time after rail-up so the first sample isn't taken on a rising supply
}

uint16_t power_battery_mv(void) {
    uint32_t node_mv = analogReadMilliVolts(PIN_BATT_SENSE);  // core API applies the factory ADC calibration
    return (uint16_t)(node_mv * BATT_DIVIDER_NUM / BATT_DIVIDER_DEN);  // undo the divider to get true battery mV
}

bool power_low_batt(void) {
    return power_battery_mv() < LOW_BATT_MV;
}
