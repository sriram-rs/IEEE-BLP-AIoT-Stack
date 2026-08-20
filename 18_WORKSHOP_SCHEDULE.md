# Workshop Schedule: Phase A (Edge Loop) + Phase B (Agentic Extension)

**Format assumed:** 3-day intensive, 09:00-17:00, one laptop per student (the
laptop is the gateway), kits shared one per 2-3 students. Phase A fills Days
1-2 and requires no LLM access from anyone. Phase B is Day 3. A weekly-course
mapping is at the end for institutions running it as 6 x 3-hour sessions.
Companion documents: `17_WORKSHOP_WORKFLOWS_EDGE_FIRST.md` (the A1-A5/B1-B3
workflows every session references), sensor decks for the teaching slides.

---

## Day 1 (Phase A): Perceive and Doubt

| Time | Session | Content and checkpoint |
|---|---|---|
| 09:00-09:30 | Setup | Registration; Python + gateway install check (`python -m gateway smoke` is the pass criterion); kit issue |
| 09:30-10:15 | S1: The AI-First Idea | The old way vs the new way (deck opening slides); the two loops; "this week you are the agent". No hardware yet, deliberately |
| 10:15-11:00 | S2: Kit Anatomy + Bring-Up | Sensor -> SIM -> BLE -> your laptop; `gateway run`; first sensors online on every laptop. Checkpoint: dashboard shows live values |
| 11:00-11:15 | Break | |
| 11:15-12:30 | S3: Perception Lab (A1) | `tool list_sensors / describe_sensor / read_latest`; reading a sensor card as a contract; the walk-away experiment: delivery ratio vs distance, front row vs back row compared |
| 12:30-13:15 | Lunch | Leave gateways logging: lunch is data |
| 13:15-14:30 | S4: Sensor Stations, Round 1 | Three stations by interface (One-Wire, I2C, GPIO); 25 min each; per sensor: what it is, its card, its failure modes, live readings |
| 14:30-15:45 | S5: Validation Lab (A2) | `tool validate_reading`, plausibility bands, rate limits; instructors inject `fault N stuck` on live SIMs; teams hunt the lie from data alone and write down the evidence chain |
| 15:45-16:00 | Break | |
| 16:00-16:45 | S6: Context + The Journal (A3) | Why "the window was opened" must be recorded (`tool annotate`); deployment discipline; set up overnight logging with a written numeric prediction per team (predict-then-measure opens tomorrow) |
| 16:45-17:00 | Day wrap | Pattern vocabulary so far: Absence of Evidence, Design for the Failure Path, Is Silence Good News? |

## Day 2 (Phase A): Act, Fuse, and Prove It

| Time | Session | Content and checkpoint |
|---|---|---|
| 09:00-09:30 | Overnight Review | Each team: prediction vs measured; `liveness` run: did anything go silent overnight and would you have known? |
| 09:30-10:45 | S7: The Rule Lifecycle (A4) | Anatomy of a rule JSON; author from the corridor-lighting template against the cards; pending -> `approve-rule` -> observe firings. Checkpoint: every team has one approved, firing rule |
| 10:45-11:00 | Break | |
| 11:00-12:30 | S8: Measure Your Rule | Predict the rule's effect in numbers first; then `tool query_timeseries` (SCT-013 / meter) to measure it; the difference between "my rule works" and "my rule saved 214 Wh" |
| 12:30-13:15 | Lunch | |
| 13:15-14:45 | S9: Fusion Without a Model (A5) | `recipe occupancy` evidence packs; teams argue a verdict (EMPTY/OCCUPIED/ACTIVE) from PIR+SPL+CO2+reed with the latency table in hand; class debate where packs disagree |
| 14:45-15:00 | Break | |
| 15:00-16:15 | S10: Phase A Assessment | Individually: one seeded-fault dataset to diagnose in writing; one rule defended orally against the cards. Pass criteria per doc 17 Section 5 |
| 16:15-17:00 | S11: The Bridge | The role-handover table: every step you did by hand, named; what an agent, MCP, and a tool call are; 10-minute teaser demo of tomorrow on the instructor account |

## Day 3 (Phase B): The Agentic Extension

| Time | Session | Content and checkpoint |
|---|---|---|
| 09:00-09:45 | S12: MCP and Governance | `gateway mcp`; how the client connects; why deploy_rule lands pending and who approves; access tiers assigned (shared account / free tier / BYOK / auditor role) |
| 09:45-11:00 | S13: Live Agentic Session | Capstone C1 run end-to-end on the projected instructor account; students take turns phrasing the questions; the class watches every tool call and maps it to the Day 1-2 step they performed by hand |
| 11:00-11:15 | Break | |
| 11:15-12:30 | S14: Pod Sessions | Pods of 3-4 by access tier; each pod drives an agent through a mini-question (comfort, cold chain, lighting); the agent must ask for context and validate before concluding; every actuation lands pending |
| 12:30-13:15 | Lunch | |
| 13:15-14:30 | S15: Audit the Agent | The core Phase B skill: review the agent's proposed rules against the cards, approve or reject in writing; one instructor-seeded wrong conclusion (via fault injection) is hidden in the sessions and must be caught |
| 14:30-15:30 | S16: The Agent Audits Itself | Re-run the Day 2 measured-rule comparison, agent-driven; compare the agent's verdict with the team's manual Day 2 verdict; where they differ, decide who is right and prove it |
| 15:30-15:45 | Break | |
| 15:45-16:30 | S17: Capstone Kickoff | Teams pick from C1-C8 (doc 15); deployment plan, sensor list, pattern callbacks named in the plan; semester or follow-up timeline |
| 16:30-17:00 | Close | Phase B assessment brief (audit-based, doc 17 Section 5); feedback; kit return or checkout for capstones |

## Weekly-Course Mapping (6 x 3 hours)

| Week | Covers | Phase |
|---|---|---|
| 1 | S1-S3 (idea, bring-up, perception) | A |
| 2 | S4-S5 (stations, validation + fault hunt) | A |
| 3 | S6-S8 (journal, rules, measured effect); logging runs between weeks, so predict-then-measure spans a full week and improves | A |
| 4 | S9-S11 (fusion, assessment, bridge) | A |
| 5 | S12-S15 (MCP, live session, pods, audit) | B |
| 6 | S16-S17 (self-audit, capstone kickoff) | B |

## Instructor Preparation Checklist

- Before Day 1: kits flashed and labelled; one rehearsal-advertiser board as
  the known-good radio reference; USB BLE dongles (1 per 6 students) for
  locked-down laptops; gateway install instructions sent ahead; verify the
  venue allows BLE and has enough mains outlets and power banks charged.
- Before Day 3: verify current free-tier MCP availability THAT WEEK (policy
  shifts; do not rely on printed claims); shared instructor account logged in
  and MCP-connected on the projector machine; seed the S15 wrong conclusion
  and note where.
- Timing honesty: S5 and S7 habitually overrun; S4 and S16 are the designed
  buffers, cut station time or the re-run before cutting the labs.
