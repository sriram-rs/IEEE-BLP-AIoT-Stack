"""Shared context handed to every MCP tool.

Tools are plain functions over this context so they can be exercised directly
by tests and by the agents' orchestrator without an MCP transport in between.
server.py wraps the same functions for Claude and other MCP clients.
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path

from ..core import PACKAGE_DIR, RULES_DIR, load_config
from ..decoder.registry import CardRegistry
from ..store.db import Store


@dataclass
class GatewayContext:
    store: Store
    registry: CardRegistry
    rules_dir: Path = RULES_DIR
    capability_token_file: Path = RULES_DIR.parent / ".capability_token"

    @classmethod
    def from_config(cls, config: dict | None = None) -> "GatewayContext":
        cfg = config or load_config()
        db_path = Path(cfg["db_path"])
        if not db_path.is_absolute():
            db_path = PACKAGE_DIR / db_path
        return cls(store=Store(db_path), registry=CardRegistry())
