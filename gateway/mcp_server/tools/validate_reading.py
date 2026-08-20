"""validate_reading: verdict + reasoning from the card's plausibility bounds.

The tool never just says yes or no; it returns the evidence chain so the model
(and the student grading the model) can inspect the reasoning.
"""

from __future__ import annotations

import time

from ..context import GatewayContext


def validate_reading(ctx: GatewayContext, sensor_uid: str, field: str,
                     value: float | None = None) -> dict:
    type_id = int(sensor_uid.split(":")[-1])
    card = next((c for c in ctx.registry.all_cards()
                 if c.sensor_type_id == type_id), None)
    if card is None:
        return {"verdict": "unknown", "reasoning": [f"no card for type {type_id}"]}

    reasoning: list[str] = []
    verdict = "plausible"

    latest = ctx.store.read_latest(sensor_uid)
    if value is None:
        entry = latest.get(field)
        if entry is None:
            return {"verdict": "unknown",
                    "reasoning": [f"no stored reading for {sensor_uid}.{field}"]}
        value = entry["value"]
        age = time.time() - entry["ts"]
        if age > card.sampling_period_s * 6:
            verdict = "stale"
            reasoning.append(
                f"latest reading is {age:.0f}s old against a {card.sampling_period_s}s "
                f"sampling period; treat as missing, not as current truth")
        if not (entry["status"] & 0x01):
            verdict = "invalid"
            reasoning.append("sensor_ok status bit is clear: the SIM itself "
                             "reports a fault; the number is not a measurement")

    bounds = card.plausibility.get(field)
    if bounds:
        if value < bounds.get("min", float("-inf")):
            verdict = "implausible"
            reasoning.append(f"{value} is below the plausibility floor {bounds['min']}")
        elif value > bounds.get("max", float("inf")):
            verdict = "implausible"
            reasoning.append(f"{value} is above the plausibility ceiling {bounds['max']}")
        else:
            reasoning.append(
                f"{value} lies inside the card's plausibility band "
                f"[{bounds.get('min')}, {bounds.get('max')}]")

        step = bounds.get("max_step_per_min")
        if step:
            hist = ctx.store.query_timeseries(
                sensor_uid, field, time.time() - 120, time.time())
            # a rate estimated over less than 30 s is noise amplification,
            # not physics; require a meaningful observation window
            if len(hist) >= 2 and (hist[-1]["ts"] - hist[0]["ts"]) >= 30:
                dt = (hist[-1]["ts"] - hist[0]["ts"]) / 60
                dv = abs(hist[-1]["value"] - hist[0]["value"]) / dt
                if dv > step:
                    verdict = "implausible"
                    reasoning.append(
                        f"rate of change {dv:.1f}/min exceeds the physical "
                        f"limit {step}/min on the card")
    else:
        reasoning.append(f"card has no plausibility bounds for {field}")

    fm = card.doc.get("failure_modes", [])
    return {
        "sensor_uid": sensor_uid,
        "field": field,
        "value": value,
        "verdict": verdict,
        "reasoning": reasoning,
        "relevant_failure_modes": fm,
    }
