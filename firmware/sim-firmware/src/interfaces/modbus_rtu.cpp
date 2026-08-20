// modbus_rtu.cpp: function-0x03 master over UART2 with DE/RE direction control.
#include "modbus_rtu.h"
#include <Arduino.h>
#include "pins.h"

#if SIM_VARIANT == 5                       // whole file only meaningful on the RS485 SIM

static HardwareSerial &s_uart = Serial2;   // UART0 is the console, UART2 drives the transceiver

// Standard Modbus CRC-16 (poly 0xA001 reflected), low byte transmitted first.
static uint16_t crc16(const uint8_t *data, uint8_t len) {
    uint16_t crc = 0xFFFF;
    for (uint8_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t b = 0; b < 8; b++)
            crc = (crc & 1) ? (crc >> 1) ^ 0xA001 : crc >> 1;
    }
    return crc;
}

void modbus_init(uint32_t baud) {
    pinMode(PIN_RS485_DE, OUTPUT);
    digitalWrite(PIN_RS485_DE, LOW);       // idle in receive: the bus must never be driven while listening
    s_uart.begin(baud, SERIAL_8N1, PIN_RS485_RX, PIN_RS485_TX);
}

bool modbus_read_holding(uint8_t addr, uint16_t reg, uint16_t n, uint16_t *words) {
    uint8_t req[8] = {
        addr, 0x03,                        // function 0x03: read holding registers
        (uint8_t)(reg >> 8), (uint8_t)(reg & 0xFF),
        (uint8_t)(n >> 8), (uint8_t)(n & 0xFF),
    };
    uint16_t crc = crc16(req, 6);
    req[6] = crc & 0xFF;                   // CRC low byte first, per the RTU spec
    req[7] = crc >> 8;

    while (s_uart.available()) s_uart.read();  // flush stale bytes so an old response can't be mistaken for this one

    digitalWrite(PIN_RS485_DE, HIGH);      // claim the bus only for the transmit window
    s_uart.write(req, 8);
    s_uart.flush();                        // block until the last stop bit is on the wire before releasing the driver
    digitalWrite(PIN_RS485_DE, LOW);

    // Expected response: addr, 0x03, bytecount, n*2 data bytes, CRC lo, CRC hi
    uint8_t expect = 3 + n * 2 + 2;
    uint8_t resp[64];
    if (expect > sizeof(resp)) return false;   // caller asked for more registers than this transport buffer supports

    uint32_t deadline = millis() + 200;    // 200 ms covers slave turnaround at 9600 baud with margin
    uint8_t got = 0;
    while (got < expect && millis() < deadline)
        if (s_uart.available()) resp[got++] = s_uart.read();

    if (got != expect) return false;                        // timeout or short frame = comms fault
    if (resp[0] != addr || resp[1] != 0x03) return false;   // exception response or wrong slave answered
    uint16_t rx_crc = resp[expect - 2] | (resp[expect - 1] << 8);
    if (crc16(resp, expect - 2) != rx_crc) return false;    // corrupted frame: reject rather than decode garbage

    for (uint16_t i = 0; i < n; i++)
        words[i] = (resp[3 + i * 2] << 8) | resp[4 + i * 2];  // register data is big-endian on the wire
    return true;
}

#endif // SIM_VARIANT == 5
