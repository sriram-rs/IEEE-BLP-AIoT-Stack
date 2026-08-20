// sensor_registry: assembles the module table from the -DSENSOR_* build flags.
// This file is the ONLY place that knows which sensors exist; adding a sensor
// to the platform = one new module .cpp + one extern/entry pair here + one
// build flag in platformio.ini + one card on the gateway.
#include "../../include/sensor_module.h"

// extern declarations for every module that might be compiled in
#ifdef SENSOR_DS18B20
extern const SensorModule MOD_DS18B20;
#endif
#ifdef SENSOR_BME688
extern const SensorModule MOD_BME688;
#endif
#ifdef SENSOR_SCD41
extern const SensorModule MOD_SCD41;
#endif
#ifdef SENSOR_VEML7700
extern const SensorModule MOD_VEML7700;
#endif
#ifdef SENSOR_PIR
extern const SensorModule MOD_PIR;
#endif
#ifdef SENSOR_REED
extern const SensorModule MOD_REED;
#endif
#ifdef SENSOR_AT42QT1010
extern const SensorModule MOD_AT42;
#endif
#ifdef SENSOR_ANALOG_420MA
extern const SensorModule MOD_ANALOG420;
#endif
#ifdef SENSOR_SPL
extern const SensorModule MOD_SPL;
#endif
#ifdef SENSOR_JSN_SR04T
extern const SensorModule MOD_JSN;
#endif
#ifdef SENSOR_SCT013
extern const SensorModule MOD_SCT013;
#endif
#ifdef SENSOR_SEN0193
extern const SensorModule MOD_SEN0193;
#endif
#ifdef SENSOR_WATER_TRACE
extern const SensorModule MOD_WATER;
#endif
#ifdef SENSOR_RS485_METER
extern const SensorModule MOD_RS485_METER;
#endif

// The table is built at compile time: excluded sensors cost zero flash.
static const SensorModule *s_modules[] = {
#ifdef SENSOR_DS18B20
    &MOD_DS18B20,
#endif
#ifdef SENSOR_BME688
    &MOD_BME688,
#endif
#ifdef SENSOR_SCD41
    &MOD_SCD41,
#endif
#ifdef SENSOR_VEML7700
    &MOD_VEML7700,
#endif
#ifdef SENSOR_PIR
    &MOD_PIR,
#endif
#ifdef SENSOR_REED
    &MOD_REED,
#endif
#ifdef SENSOR_AT42QT1010
    &MOD_AT42,
#endif
#ifdef SENSOR_ANALOG_420MA
    &MOD_ANALOG420,
#endif
#ifdef SENSOR_SPL
    &MOD_SPL,
#endif
#ifdef SENSOR_JSN_SR04T
    &MOD_JSN,
#endif
#ifdef SENSOR_SCT013
    &MOD_SCT013,
#endif
#ifdef SENSOR_SEN0193
    &MOD_SEN0193,
#endif
#ifdef SENSOR_WATER_TRACE
    &MOD_WATER,
#endif
#ifdef SENSOR_RS485_METER
    &MOD_RS485_METER,
#endif
};

const SensorModule **sensor_registry(uint8_t *count) {
    *count = sizeof(s_modules) / sizeof(s_modules[0]);
    return s_modules;
}
