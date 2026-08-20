// adc_in: calibrated, oversampled ADC reads for the analog SIM.
// Modules ask for millivolts; the ESP32 ADC's nonlinearity and noise are
// handled here so no sensor module contains raw ADC counts.
#pragma once
#include <stdint.h>

void adc_in_init(uint8_t pin);                     // set 11 dB attenuation once per pin
uint16_t adc_read_mv(uint8_t pin, uint8_t oversample);  // mean of 2^oversample calibrated reads
uint16_t adc_read_rms_mv(uint8_t pin, uint16_t n_samples, uint16_t sample_period_us);
// ^ AC RMS around the DC bias: samples fast, removes the mean, returns RMS in
//   mV. Used by the SCT-013 module; kept here because RMS-from-ADC is an
//   interface skill, not a sensor-specific one.
