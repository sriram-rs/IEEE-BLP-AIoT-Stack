// power: sensor rail control and battery sensing.
#pragma once
#include <stdint.h>

void power_init(void);          // configures the rail-enable pin and turns the sensor rail on
void power_rail(bool on);       // lets a module or selftest power-cycle a hung sensor
uint16_t power_battery_mv(void);// battery voltage through the divider, in millivolts
bool power_low_batt(void);      // true when battery is below LOW_BATT_MV -> low_batt status bit
