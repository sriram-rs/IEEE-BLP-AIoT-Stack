// rs485_meter_mod: type 5, SIM5, Modbus RTU energy meter.
// Payload (card 05): u16 voltage_v*100, u16 power_w, u32 energy_kwh*100. 8 bytes.
//
// HANDOVER NOTE: register addresses and scalings below are for the Rev5
// meter's documented map (voltage at 0x34A, value/100). The firmware team
// must verify every address and scale against the actual meter datasheet;
// the gateway serves the same map as an MCP resource so both sides can be
// checked against one document (Contracts All the Way Down).
#ifdef SENSOR_RS485_METER
#include <Arduino.h>
#include "../../include/sensor_module.h"
#include "../interfaces/modbus_rtu.h"

#define METER_ADDR      0x01             // slave address; Rev5 notes 0x340 as a doc value, but RTU addresses are 1-247: VERIFY with the meter config
#define REG_VOLTAGE     0x034A           // R-phase voltage, 2 words, /100 per the Rev5 decode example
#define REG_ACT_POWER   0x0356           // active power register: PLACEHOLDER, verify against the meter map
#define REG_ACT_ENERGY  0x0360           // active energy register: PLACEHOLDER, verify against the meter map
#define MODBUS_BAUD     9600             // the near-universal panel-meter default

static bool meter_init(void) {
    modbus_init(MODBUS_BAUD);
    uint16_t w[2];
    return modbus_read_holding(METER_ADDR, REG_VOLTAGE, 2, w);  // a successful register read is the presence check
}

static bool meter_sample(uint8_t *payload, uint8_t *len) {
    *len = 8;
    uint16_t w[2];

    if (!modbus_read_holding(METER_ADDR, REG_VOLTAGE, 2, w)) return false;  // comms fault: sensor_ok cleared, no stale values resent
    uint32_t volt_raw = ((uint32_t)w[0] << 16) | w[1];         // 2-word big-endian per the Rev5 decode example
    put_u16(payload, (uint16_t)volt_raw);                      // register/100 = volts, payload wants volts*100: raw passes straight through

    if (!modbus_read_holding(METER_ADDR, REG_ACT_POWER, 2, w)) return false;
    uint32_t power_raw = ((uint32_t)w[0] << 16) | w[1];
    put_u16(payload + 2, (uint16_t)(power_raw > 65535 ? 65535 : power_raw));  // clamp: payload field is u16 watts

    if (!modbus_read_holding(METER_ADDR, REG_ACT_ENERGY, 2, w)) return false;
    uint32_t energy_raw = ((uint32_t)w[0] << 16) | w[1];
    put_u32(payload + 4, energy_raw);                          // kWh*100 as u32, wraps after ~42 GWh: not a classroom concern
    return true;
}

extern const SensorModule MOD_RS485_METER = {
    5, 1, 10000, "RS485-METER",          // 10 s: energy accumulates slowly and Modbus polls cost bus time
    meter_init, meter_sample,
};
#endif // SENSOR_RS485_METER
