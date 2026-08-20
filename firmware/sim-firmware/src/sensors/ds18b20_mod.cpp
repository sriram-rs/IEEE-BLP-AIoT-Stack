// ds18b20_mod: type 1, SIM1, One-Wire temperature.
// Payload (card 01): int16 temperature_c * 100. 2 bytes.
#ifdef SENSOR_DS18B20
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "../../include/sensor_module.h"
#include "../../include/pins.h"

static OneWire s_wire(PIN_ONEWIRE_DATA);
static DallasTemperature s_dallas(&s_wire);

static bool ds_init(void) {
    s_dallas.begin();
    s_dallas.setResolution(12);                  // 12-bit = 0.0625 C steps: matches the card's 0.01 C payload scale comfortably
    return s_dallas.getDeviceCount() > 0;        // presence check for selftest; daisy-chained probes all count
}

static bool ds_sample(uint8_t *payload, uint8_t *len) {
    s_dallas.requestTemperatures();              // blocking ~750 ms at 12-bit; acceptable at a 5 s period
    float t = s_dallas.getTempCByIndex(0);       // index 0: first probe; multi-probe support is a documented extension point
    *len = 2;
    if (t == DEVICE_DISCONNECTED_C || t == 85.0f) {  // -127 = bus fault; exactly 85.00 = power-on default, both are known-bad per the card
        put_i16(payload, (int16_t)(t * 100));    // still report the raw value: the gateway card teaches WHY it is bad
        return false;                            // sensor_ok cleared: a bad number must never look like a measurement
    }
    put_i16(payload, (int16_t)(t * 100.0f));
    return true;
}

extern const SensorModule MOD_DS18B20 = {
    1, 1, 5000, "DS18B20",                       // type 1, schema 1, 5 s period per the card
    ds_init, ds_sample,
};
#endif // SENSOR_DS18B20
