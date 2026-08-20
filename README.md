# AIoT and Climate Change: AI-First Course Package

Generated 5 August 2026. Supersedes the sensor-chapter structure of the Rev5 manual; the Rev5 hardware facts (packaging story, compatibility matrix, datasheet-reading habit) carry forward inside the new decks.

## Contents

| File | Purpose |
|------|---------|
| `00_ARCHITECTURE_AND_CODE_STRUCTURE.md` | System architecture, BLE payload spec, sensor card schema, SIM firmware layout, gateway/MCP layout, agent orchestration, capstone catalog C1-C8, slide conventions |
| `sensor_decks/01_DS18B20_temperature.md` | Temperature, SIM1, One-Wire |
| `sensor_decks/02_BME688_gas_iaq.md` | Gas/IAQ + T/RH/P, SIM2, I2C |
| `sensor_decks/03_PIR_motion.md` | Motion, SIM3, GPIO |
| `sensor_decks/04_ANALOG_4-20mA_industrial_transmitters.md` | Industrial analog standard, SIM4 |
| `sensor_decks/05_RS485_industrial_digital_sensors.md` | Industrial digital standard, SIM5 |
| `sensor_decks/06_SCD41_co2.md` | CO2, SIM2, I2C |
| `sensor_decks/07_VEML7700_lux.md` | Illuminance, SIM2, I2C |
| `sensor_decks/08_SPL_sound_level.md` | Sound pressure level, SIM4 |
| `sensor_decks/09_JSN-SR04T_ultrasonic_distance.md` | Distance/level, SIM4 (pulse-width, see note in architecture doc) |
| `sensor_decks/10_REED_switch_contact.md` | Open/closed state, SIM3 |
| `sensor_decks/11_SCT013_current.md` | AC current, SIM4 |
| `sensor_decks/12_SEN0193_soil_moisture.md` | Soil moisture, SIM4 |
| `sensor_decks/13_WATER_LEVEL_bare_trace.md` | Water presence, SIM4 |
| `sensor_decks/14_AT42QT1010_proximity.md` | Proximity/touch, SIM3 |
| `15_CAPSTONES_WITH_PATTERN_CALLBACKS.md` | Capstone briefs C1-C8 with the agentic patterns called back by name, orchestration sketches, pattern-aware assessment, coverage matrix |
| `16_AGENTIC_ARCHITECTURE_BRIEF_FOR_FIRMWARE_TEAM.md` | Handover brief: agentic AI vs assistant AI, the contract chain, every firmware design decision mapped to its agentic reason, bring-up checklist |
| `17_WORKSHOP_WORKFLOWS_EDGE_FIRST.md` | SIM/gateway/system workflows; Phase A edge loop with zero LLM (student plays the agent via CLI tools), Phase B agentic cloud loop as extension; cheat sheet |
| `18_WORKSHOP_SCHEDULE.md` | 3-day session-by-session schedule with timings (Phase A Days 1-2, Phase B Day 3), 6-week mapping, instructor prep checklist |
| `CONVERSATION_LOG_2026-08-05.md` | The design conversation with the course owner, prompts verbatim |
| `gateway/` | Gateway codebase: BLE scan, card-driven decode, SQLite store, MCP server, rule engine, agents, dashboard |
| `firmware/rehearsal_advertiser/` | Single-sketch ESP32 known-good radio reference |
| `firmware/sim-firmware/` | Production SIM firmware: PlatformIO, 5 variants, modular sensors, pins in one header |

Each deck: nine slides. Slides 1-3 are the AI-first opening, kept deliberately simple for a wide audience: the old way versus the new way of perceiving this quantity, what the AI must know about this sensor to be trusted with it, and one named agentic design pattern per deck (the pattern vocabulary table is in the architecture doc, Section 9). Slides 4-9: what it is, practice, technical card, climate change, fusion partners, capstone. Full spoken narration per slide. Packaged sensor dimensions and connector details are `[PLACEHOLDER]` pending final packaging.

## How to turn a deck into a PPT

Each `## Slide` heading is one slide; `**Slide content**` bullets go on the slide body; `**Narration**` goes into the speaker notes. A python-pptx script can consume these files mechanically since the structure is fixed.
