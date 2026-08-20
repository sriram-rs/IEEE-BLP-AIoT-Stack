"""Passive BLE advertisement scanner.

The only platform-facing module in the gateway. bleak selects its backend at
runtime: WinRT on Windows, BlueZ on Linux (Raspberry Pi, Uno Q), CoreBluetooth
on macOS. Nothing else in the codebase knows which radio is underneath.
"""

from __future__ import annotations

import asyncio
import time
from collections.abc import Callable

from ..core import COMPANY_ID, RawFrame, parse_manufacturer_data

try:
    from bleak import BleakScanner
    HAVE_BLEAK = True
except ImportError:
    HAVE_BLEAK = False


class BleSource:
    """Streams RawFrame objects from live BLE advertisements."""

    def __init__(self, company_id: int = COMPANY_ID, adapter: str | None = None,
                 kit_id: int | None = None):
        if not HAVE_BLEAK:
            raise RuntimeError(
                "bleak is not installed. Run: pip install bleak\n"
                "For development without a radio, use the simulator: python -m gateway simulate"
            )
        self.company_id = company_id
        self.adapter = adapter
        self.kit_id = kit_id

    async def run(self, on_frame: Callable[[RawFrame], None]) -> None:
        def detection(device, adv):
            data = adv.manufacturer_data.get(self.company_id)
            if data is None:
                return
            frame = parse_manufacturer_data(bytes(data), rx_time=time.time(),
                                            rssi=adv.rssi)
            if frame is None:
                return
            if self.kit_id is not None and frame.kit_id != self.kit_id:
                return
            on_frame(frame)

        kwargs = {"detection_callback": detection, "scanning_mode": "passive"}
        if self.adapter:
            kwargs["adapter"] = self.adapter  # BlueZ only; ignored elsewhere
        try:
            scanner = BleakScanner(**kwargs)
            async with scanner:
                while True:
                    await asyncio.sleep(3600)
        except Exception:
            # WinRT and some BlueZ builds reject passive mode; active scan still
            # receives the same advertisement payloads.
            kwargs.pop("scanning_mode", None)
            scanner = BleakScanner(**kwargs)
            async with scanner:
                while True:
                    await asyncio.sleep(3600)
