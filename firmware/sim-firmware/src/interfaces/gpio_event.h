// gpio_event: debounced interrupt edge capture with event counters.
// Shared by PIR, reed, and AT42QT1010: all three are "a digital line changed
// state" sensors; only their debounce times and polarities differ.
#pragma once
#include <stdint.h>

// Register a pin for edge capture. Returns a channel handle (0..3).
// pull_up: enable the internal pull-up (reed switch to GND needs it).
// debounce_ms: edges closer together than this are one event (contact bounce).
int8_t gpio_event_attach(uint8_t pin, bool pull_up, uint16_t debounce_ms);

uint8_t  gpio_event_level(int8_t ch);   // current debounced level (0/1)
uint16_t gpio_event_count(int8_t ch);   // rising-edge count since boot, wraps at 65535
