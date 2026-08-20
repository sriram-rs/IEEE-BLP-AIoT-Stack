"""annotate: the deployment journal.

Physical context the sensors cannot see ("window opened", "sensor moved to
the north wall", "kettle acceptance test passed at 8.3 A") becomes queryable
data. Agents are expected to ask users for this context and write it here.
"""

from __future__ import annotations

from ..context import GatewayContext


def annotate(ctx: GatewayContext, note: str, sensor_uid: str | None = None,
             author: str | None = None, ts: float | None = None) -> dict:
    ann_id = ctx.store.annotate(note, sensor_uid, author, ts)
    return {"annotation_id": ann_id, "note": note, "sensor_uid": sensor_uid}


def list_annotations(ctx: GatewayContext, since: float = 0.0) -> list[dict]:
    return ctx.store.annotations(since)
