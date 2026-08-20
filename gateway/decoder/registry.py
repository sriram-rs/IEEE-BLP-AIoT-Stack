"""Card registry: (sensor_type_id, schema_version) -> parser built from the card.

The card is the single source of truth for payload layout. There is no
hand-written parser per sensor; adding a sensor to the platform means adding a
card, exactly as the architecture document promises third parties.
"""

from __future__ import annotations

import json
import struct
from pathlib import Path

from ..core import CARDS_DIR, RawFrame

_ENCODINGS = {
    "uint8": ("<B", 1),
    "int8": ("<b", 1),
    "uint16": ("<H", 2),
    "int16": ("<h", 2),
    "uint32": ("<I", 4),
    "int32": ("<i", 4),
}


class Card:
    def __init__(self, doc: dict, path: Path):
        self.doc = doc
        self.path = path
        self.sensor_type_id = int(doc["sensor_type_id"])
        self.schema_version = int(doc["schema_version"])
        self.part = doc.get("part", "unknown")
        self.measurands = doc.get("measurands", [])
        self.plausibility = doc.get("plausibility", {})
        self.sampling_period_s = float(doc.get("sampling_period_s", 5))

    def decode(self, payload: bytes) -> dict[str, float]:
        values: dict[str, float] = {}
        for m in self.measurands:
            pf = m.get("payload_field")
            if not pf:
                continue
            fmt, size = _ENCODINGS[pf["encoding"]]
            off = pf["offset"]
            if off + size > len(payload):
                continue  # truncated frame: decode what is present
            raw = struct.unpack_from(fmt, payload, off)[0]
            values[m["name"]] = raw * pf.get("scale", 1)
        return values


class CardRegistry:
    def __init__(self, cards_dir: str | Path = CARDS_DIR):
        self.cards_dir = Path(cards_dir)
        self._cards: dict[tuple[int, int], Card] = {}
        self.reload()

    def reload(self) -> None:
        self._cards.clear()
        for path in sorted(self.cards_dir.glob("*.json")):
            with open(path, encoding="utf-8") as fh:
                doc = json.load(fh)
            card = Card(doc, path)
            self._cards[(card.sensor_type_id, card.schema_version)] = card

    def resolve(self, frame: RawFrame) -> Card | None:
        card = self._cards.get((frame.sensor_type_id, frame.schema_version))
        if card is None:
            # forward-compatibility: fall back to the newest known schema for
            # this type so an old gateway degrades gracefully, not silently
            candidates = [c for (tid, _), c in self._cards.items()
                          if tid == frame.sensor_type_id]
            card = max(candidates, key=lambda c: c.schema_version, default=None)
        return card

    def decode(self, frame: RawFrame) -> tuple[Card | None, dict[str, float]]:
        card = self.resolve(frame)
        if card is None:
            return None, {}
        return card, card.decode(frame.payload)

    def all_cards(self) -> list[Card]:
        return list(self._cards.values())
