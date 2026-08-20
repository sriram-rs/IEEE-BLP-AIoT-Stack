// pins.h: THE single place where every pin assignment lives.
// Firmware team: when the SIM PCB pinout is final, edit ONLY this file (or
// override any macro from platformio.ini with -DPIN_X=n). No sensor or
// interface module names a GPIO number directly.
#pragma once

// ---------- pins common to every SIM variant ----------
#ifndef PIN_SENSOR_RAIL_EN
#define PIN_SENSOR_RAIL_EN 25      // high-side switch for the sensor supply rail; lets firmware power-cycle a hung sensor
#endif
#ifndef PIN_BATT_SENSE
#define PIN_BATT_SENSE     35      // ADC input on the battery divider; input-only pin is fine here
#endif
#ifndef BATT_DIVIDER_NUM           // divider ratio as a fraction, e.g. 2/1 for equal resistors
#define BATT_DIVIDER_NUM   2       // numerator: battery mV = measured mV * NUM / DEN
#endif
#ifndef BATT_DIVIDER_DEN
#define BATT_DIVIDER_DEN   1
#endif

// ---------- SIM1: One-Wire ----------
#if SIM_VARIANT == 1
#ifndef PIN_ONEWIRE_DATA
#define PIN_ONEWIRE_DATA   4       // DS18B20 bus; external 4.7k pull-up to 3V3 on the PCB
#endif
#endif

// ---------- SIM2: I2C ----------
#if SIM_VARIANT == 2
#ifndef PIN_I2C_SDA
#define PIN_I2C_SDA        21
#endif
#ifndef PIN_I2C_SCL
#define PIN_I2C_SCL        22
#endif
#endif

// ---------- SIM3: GPIO event sensors ----------
#if SIM_VARIANT == 3
#ifndef PIN_PIR_OUT
#define PIN_PIR_OUT        27      // PIR digital output; interrupt-capable pin required
#endif
#ifndef PIN_REED_IN
#define PIN_REED_IN        26      // reed switch to GND; internal pull-up used
#endif
#ifndef PIN_AT42_OUT
#define PIN_AT42_OUT       33      // AT42QT1010 OUT pin
#endif
#endif

// ---------- SIM4: analog + pulse sensors ----------
#if SIM_VARIANT == 4
#ifndef PIN_ADC_420MA
#define PIN_ADC_420MA      36      // burden-resistor voltage for the 4-20 mA loop
#endif
#ifndef PIN_ADC_SPL
#define PIN_ADC_SPL        39      // SPL envelope DC level
#endif
#ifndef PIN_ADC_SCT013
#define PIN_ADC_SCT013     34      // biased CT output; AC around mid-rail
#endif
#ifndef PIN_ADC_SEN0193
#define PIN_ADC_SEN0193    32      // soil probe output through the divider that keeps dry-air < 2.8 V
#endif
#ifndef PIN_ADC_WATER
#define PIN_ADC_WATER      33      // water-trace sense node (pull-up to excitation)
#endif
#ifndef PIN_WATER_EXCITE
#define PIN_WATER_EXCITE   23      // duty-cycled excitation for the bare traces: prevents electrolysis
#endif
#ifndef PIN_JSN_TRIG
#define PIN_JSN_TRIG       18      // JSN-SR04T trigger out; connector must expose this line
#endif
#ifndef PIN_JSN_ECHO
#define PIN_JSN_ECHO       19      // JSN-SR04T echo in; interrupt-capable pin required
#endif
#ifndef R_BURDEN_420MA_OHM
#define R_BURDEN_420MA_OHM 100     // 4-20 mA burden: 100 ohm -> 0.4-2.0 V, inside the ADC's linear region
#endif
#endif

// ---------- SIM5: RS485 ----------
#if SIM_VARIANT == 5
#ifndef PIN_RS485_TX
#define PIN_RS485_TX       17
#endif
#ifndef PIN_RS485_RX
#define PIN_RS485_RX       16
#endif
#ifndef PIN_RS485_DE
#define PIN_RS485_DE       4       // driver-enable (DE/RE tied); high = transmit, low = listen
#endif
#endif
