"""RadioStudio AIoT gateway: BLE scan -> card-driven decode -> timeseries store -> MCP endpoint.

The gateway is a contract, not a board. This package runs unchanged on Windows
(development), Raspberry Pi, and Arduino Uno Q (Linux side). Platform-specific
code is confined to scanner/ble_scan.py (bleak backend).
"""

__version__ = "0.1.0"
