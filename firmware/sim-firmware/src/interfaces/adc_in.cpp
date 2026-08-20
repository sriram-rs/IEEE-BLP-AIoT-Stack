// adc_in.cpp: oversampling and RMS extraction over the calibrated core API.
#include "adc_in.h"
#include <Arduino.h>

void adc_in_init(uint8_t pin) {
    analogSetPinAttenuation(pin, ADC_11db);        // 11 dB: linear to ~3.1 V, matching the SIM4 front-end scaling
}

uint16_t adc_read_mv(uint8_t pin, uint8_t oversample) {
    uint32_t n = 1u << oversample;                 // 2^k samples: mean improves SNR by sqrt(n) for white noise
    uint32_t acc = 0;
    for (uint32_t i = 0; i < n; i++) acc += analogReadMilliVolts(pin);  // core API applies factory calibration per chip
    return (uint16_t)(acc / n);
}

uint16_t adc_read_rms_mv(uint8_t pin, uint16_t n_samples, uint16_t sample_period_us) {
    // Two passes are avoided by accumulating sum and sum-of-squares in one
    // sweep; 64-bit accumulators prevent overflow at 3300 mV * 2048 samples.
    uint64_t sum = 0, sumsq = 0;
    for (uint16_t i = 0; i < n_samples; i++) {
        uint32_t mv = analogReadMilliVolts(pin);
        sum += mv;
        sumsq += (uint64_t)mv * mv;
        delayMicroseconds(sample_period_us);       // paced sampling: ~1 kHz covers 20 x 50 Hz mains cycles in 1024 samples
    }
    uint64_t mean = sum / n_samples;
    uint64_t meansq = sumsq / n_samples;
    uint64_t var = meansq > mean * mean ? meansq - mean * mean : 0;  // clamp negative variance from integer truncation
    return (uint16_t)sqrt((double)var);            // RMS of the AC component = sqrt(E[x^2] - E[x]^2)
}
