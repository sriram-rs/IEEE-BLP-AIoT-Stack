// gpio_event.cpp: ISR-driven edge capture, 4 channels.
#include "gpio_event.h"
#include <Arduino.h>

#define MAX_CH 4

struct Channel {
    uint8_t pin;
    volatile uint8_t level;
    volatile uint16_t count;
    volatile uint32_t last_edge_ms;
    uint16_t debounce_ms;
    bool used;
};

static Channel s_ch[MAX_CH];

// One ISR per channel via template trick avoided for clarity: a shared ISR
// with a channel argument through attachInterruptArg keeps this reviewable.
static void IRAM_ATTR isr_handler(void *arg) {
    Channel *c = (Channel *)arg;
    uint32_t now = millis();
    if (now - c->last_edge_ms < c->debounce_ms) return;  // bounce suppression: edges inside the window are the same physical event
    c->last_edge_ms = now;
    uint8_t lvl = digitalRead(c->pin);
    if (lvl && !c->level) c->count++;                    // count rising edges only: "event happened", not both transitions
    c->level = lvl;
}

int8_t gpio_event_attach(uint8_t pin, bool pull_up, uint16_t debounce_ms) {
    for (int8_t i = 0; i < MAX_CH; i++) {
        if (s_ch[i].used) continue;
        s_ch[i] = {pin, 0, 0, 0, debounce_ms, true};
        pinMode(pin, pull_up ? INPUT_PULLUP : INPUT);
        s_ch[i].level = digitalRead(pin);                // seed with the real level so the first frame is honest
        attachInterruptArg(digitalPinToInterrupt(pin), isr_handler, &s_ch[i], CHANGE);  // CHANGE not RISING: we track level as well as count
        return i;
    }
    return -1;                                           // out of channels: caller must treat as init failure
}

uint8_t gpio_event_level(int8_t ch)  { return ch >= 0 ? s_ch[ch].level : 0; }
uint16_t gpio_event_count(int8_t ch) { return ch >= 0 ? s_ch[ch].count : 0; }
