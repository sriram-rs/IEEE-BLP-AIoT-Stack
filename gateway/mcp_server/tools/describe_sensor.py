"""describe_sensor: return the full card for a sensor uid or type id."""

from __future__ import annotations

from ..context import GatewayContext


def describe_sensor(ctx: GatewayContext, sensor: str) -> dict:
    """sensor: a uid like '1:6' or a bare sensor_type_id like '6'."""
    type_id = int(sensor.split(":")[-1])
    for card in ctx.registry.all_cards():
        if card.sensor_type_id == type_id:
            return card.doc
    return {"error": f"no card registered for sensor_type_id {type_id}",
            "known_types": sorted(c.sensor_type_id for c in ctx.registry.all_cards())}
