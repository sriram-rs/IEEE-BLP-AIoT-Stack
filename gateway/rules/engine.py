"""Deterministic edge rule engine. No LLM in this path, ever.

Rules are JSON files in rules.d/. The agent may author them (deploy_rule
tool), but a rule only runs after a human approves it: deploy_rule writes
`<name>.json.pending`; `python -m gateway approve-rule <name>` renames it to
`<name>.json`. The engine loads only approved files.

Rule spec:
{
  "name": "corridor_lighting",
  "description": "lights on only when moving people need them",
  "when": {"all": [
    {"sensor": "1:7", "field": "lux", "op": "<", "value": 300, "for_s": 30},
    {"sensor": "1:3", "field": "motion", "op": "==", "value": 1, "within_s": 60}
  ]},
  "on_fault": "skip",              # skip | fire; skip = never act on bad data
  "action": {"type": "log", "message": "lights ON"},
  "cooldown_s": 300
}

Condition semantics:
- op: <, <=, >, >=, ==, !=  against the latest value of sensor.field
- for_s: condition must have held continuously for this long
- within_s: condition must have been true at least once in this window
Action types: log (stdout + annotation), annotate, webhook (POST JSON to url),
gpio (no-op stub here; the Pi/Uno Q port maps it to a real pin driver).
"""

from __future__ import annotations

import json
import time
import urllib.request
from pathlib import Path

from ..core import RULES_DIR, STATUS_SENSOR_OK

_OPS = {
    "<": lambda a, b: a < b, "<=": lambda a, b: a <= b,
    ">": lambda a, b: a > b, ">=": lambda a, b: a >= b,
    "==": lambda a, b: a == b, "!=": lambda a, b: a != b,
}


class _CondState:
    def __init__(self):
        self.true_since: float | None = None
        self.last_true: float | None = None


class RuleEngine:
    def __init__(self, store, rules_dir: str | Path = RULES_DIR):
        self.store = store
        self.rules_dir = Path(rules_dir)
        self.rules: list[dict] = []
        self._state: dict[tuple[str, int], _CondState] = {}
        self._last_fired: dict[str, float] = {}
        self._latest: dict[tuple[str, str], tuple[float, float, int]] = {}
        self.fired_log: list[dict] = []
        self.reload()

    def reload(self) -> None:
        self.rules = []
        if not self.rules_dir.exists():
            return
        for path in sorted(self.rules_dir.glob("*.json")):
            try:
                with open(path, encoding="utf-8") as fh:
                    self.rules.append(json.load(fh))
            except (json.JSONDecodeError, OSError) as exc:
                print(f"[rules] skipping {path.name}: {exc}")

    # The engine is fed by the pipeline; it keeps its own latest-value cache so
    # evaluation never blocks on database reads.
    def evaluate(self, sensor_uid: str, values: dict[str, float], status: int) -> None:
        now = time.time()
        for field, value in values.items():
            self._latest[(sensor_uid, field)] = (value, now, status)
        for rule in self.rules:
            self._eval_rule(rule, now)

    def _eval_rule(self, rule: dict, now: float) -> None:
        name = rule.get("name", "unnamed")
        cooldown = rule.get("cooldown_s", 0)
        if now - self._last_fired.get(name, 0) < cooldown:
            return
        conds = rule.get("when", {}).get("all", [])
        if not conds:
            return
        for idx, cond in enumerate(conds):
            if not self._eval_cond(name, idx, cond, rule.get("on_fault", "skip"), now):
                return
        self._last_fired[name] = now
        self._fire(rule, now)

    def _eval_cond(self, rule_name: str, idx: int, cond: dict,
                   on_fault: str, now: float) -> bool:
        key = (rule_name, idx)
        st = self._state.setdefault(key, _CondState())
        latest = self._latest.get((cond["sensor"], cond["field"]))
        if latest is None:
            return False
        value, ts, status = latest
        if on_fault == "skip" and not (status & STATUS_SENSOR_OK):
            # bad data must never look like a decision input
            st.true_since = None
            return False
        is_true = _OPS[cond["op"]](value, cond["value"])
        if is_true:
            if st.true_since is None:
                st.true_since = now
            st.last_true = now
        else:
            st.true_since = None
        if "for_s" in cond:
            return st.true_since is not None and now - st.true_since >= cond["for_s"]
        if "within_s" in cond:
            return st.last_true is not None and now - st.last_true <= cond["within_s"]
        return is_true

    def _fire(self, rule: dict, now: float) -> None:
        action = rule.get("action", {"type": "log"})
        record = {"rule": rule.get("name"), "ts": now, "action": action.get("type")}
        self.fired_log.append(record)
        kind = action.get("type", "log")
        message = action.get("message", f"rule {rule.get('name')} fired")
        if kind in ("log", "annotate"):
            print(f"[rule:{rule.get('name')}] {message}")
            self.store.annotate(f"[rule:{rule.get('name')}] {message}",
                                author="rule-engine", ts=now)
        elif kind == "webhook":
            try:
                req = urllib.request.Request(
                    action["url"],
                    data=json.dumps(record).encode(),
                    headers={"Content-Type": "application/json"})
                urllib.request.urlopen(req, timeout=5)
            except Exception as exc:
                print(f"[rule:{rule.get('name')}] webhook failed: {exc}")
        elif kind == "gpio":
            # Port point: on Raspberry Pi / Uno Q, replace this stub with a
            # gpiozero/libgpiod driver. The rule spec does not change.
            print(f"[rule:{rule.get('name')}] gpio stub: "
                  f"pin={action.get('pin')} state={action.get('state')}")
