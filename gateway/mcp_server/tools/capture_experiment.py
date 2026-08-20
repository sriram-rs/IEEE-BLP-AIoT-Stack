"""capture_experiment: named multi-sensor capture returning a dataset handle."""

from __future__ import annotations

import time

from ..context import GatewayContext


def capture_experiment(ctx: GatewayContext, name: str, sensors: list[str],
                       duration_s: float | None = None,
                       sampling: str | None = None) -> dict:
    """Registers the capture window. Ingest continues regardless; the handle
    scopes later queries to the experiment's sensors and time span. If
    duration_s is given the window closes automatically on first read after
    expiry; otherwise call end_experiment."""
    exp_id = ctx.store.start_experiment(name, sensors, sampling,
                                        notes=f"duration_s={duration_s}")
    return {"experiment_id": exp_id, "name": name, "sensors": sensors,
            "started": time.time(), "duration_s": duration_s}


def end_experiment(ctx: GatewayContext, experiment_id: int) -> dict:
    ctx.store.end_experiment(experiment_id)
    return ctx.store.get_experiment(experiment_id) or {"error": "unknown experiment"}


def get_experiment(ctx: GatewayContext, experiment_id: int) -> dict:
    doc = ctx.store.get_experiment(experiment_id)
    return doc or {"error": "unknown experiment"}
