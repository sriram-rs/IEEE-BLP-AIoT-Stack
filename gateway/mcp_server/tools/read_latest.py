"""read_latest: most recent value per measurand for one sensor."""

from __future__ import annotations

import time

from ..context import GatewayContext


def read_latest(ctx: GatewayContext, sensor_uid: str) -> dict:
    latest = ctx.store.read_latest(sensor_uid)
    if not latest:
        return {"error": f"no readings stored for {sensor_uid}"}
    now = time.time()
    return {
        "sensor_uid": sensor_uid,
        "fields": {
            f: {
                "value": d["value"],
                "age_s": round(now - d["ts"], 1),
                "sensor_ok": bool(d["status"] & 0x01),
            }
            for f, d in latest.items()
        },
    }
