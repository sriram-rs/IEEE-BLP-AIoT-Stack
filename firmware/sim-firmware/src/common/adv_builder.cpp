// adv_builder.cpp: the one place frame bytes are laid out on the SIM side.
// Byte-for-byte mirror of gateway/core.py HEADER; the rehearsal advertiser
// and gateway/scanner/sim_source.py are the executable cross-references.
#include "adv_builder.h"
#include <BLEDevice.h>
#include <BLEAdvertising.h>
#include "sim_config.h"

static BLEAdvertising *s_adv = nullptr;   // reused across publishes; re-creating leaks in the ESP32 BLE stack

void adv_init(void) {
    BLEDevice::init("");                  // empty name: anonymous beacon, keeps the 31-byte budget for data
    s_adv = BLEDevice::getAdvertising();
    s_adv->setMinInterval(ADV_REPEAT_INTERVAL_UNITS);  // repeat each frame every 100 ms so scan windows rarely miss a seq
    s_adv->setMaxInterval(ADV_REPEAT_INTERVAL_UNITS);
}

void adv_publish(uint8_t type_id, uint8_t schema, uint16_t seq,
                 uint32_t tick_ms, uint8_t status,
                 const uint8_t *payload, uint8_t len) {
    if (len > MAX_PAYLOAD_LEN) len = MAX_PAYLOAD_LEN;  // hard clamp: an oversized payload must never push the adv past 31 bytes

    // Manufacturer data = company ID (LE) + 11-byte CONTRACT header + payload
    uint8_t mfg[2 + 11 + MAX_PAYLOAD_LEN];
    mfg[0]  = COMPANY_ID & 0xFF;
    mfg[1]  = COMPANY_ID >> 8;
    mfg[2]  = KIT_ID & 0xFF;              // kit_id u16 LE
    mfg[3]  = KIT_ID >> 8;
    mfg[4]  = type_id;                    // resolves the sensor card on the gateway
    mfg[5]  = schema;                     // payload layout version
    mfg[6]  = seq & 0xFF;                 // seq u16 LE: the packet-loss detector
    mfg[7]  = seq >> 8;
    mfg[8]  = tick_ms & 0xFF;             // tick_ms u32 LE: jitter-free time base
    mfg[9]  = (tick_ms >> 8) & 0xFF;
    mfg[10] = (tick_ms >> 16) & 0xFF;
    mfg[11] = (tick_ms >> 24) & 0xFF;
    mfg[12] = status;
    for (uint8_t i = 0; i < len; i++) mfg[13 + i] = payload[i];

    String data;
    for (uint8_t i = 0; i < 13 + len; i++) data += (char)mfg[i];

    BLEAdvertisementData adv;
    adv.setFlags(0x06);                   // general discoverable, BR/EDR unsupported: standard beacon flags
    adv.setManufacturerData(data);
    s_adv->stop();                        // payload swap requires advertising to be stopped
    s_adv->setAdvertisementData(adv);
    s_adv->start();
}
