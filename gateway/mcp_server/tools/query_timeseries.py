"""query_timeseries: raw or aggregated series over a window."""

from __future__ import annotations

from ..context import GatewayContext


def query_timeseries(ctx: GatewayContext, sensor_uid: str, field: str,
                     start: float, end: float,
                     agg: str | None = None, bucket_s: int = 60) -> dict:
    points = ctx.store.query_timeseries(sensor_uid, field, start, end, agg, bucket_s)
    return {
        "sensor_uid": sensor_uid,
        "field": field,
        "start": start,
        "end": end,
        "agg": agg,
        "bucket_s": bucket_s if agg else None,
        "n": len(points),
        "points": points,
    }
