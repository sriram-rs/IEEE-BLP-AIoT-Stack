# Setup Scripts Verification (2026-08-20)

Branch: `feature/onboarding-scripts`

This records the checks run against the new student setup tooling
(`start_installation.py`, `setup.sh`, `setup.bat`, `gateway.sh`,
`gateway.bat`) before asking for review. All checks below were run on this
Linux machine; the Windows-specific checks still need a real Windows
machine, since none is available here.

## Bug found and fixed along the way

The very first test run failed the gateway's own self-test with:
`cards loaded (14 expected) got 15`.

Cause: `gateway/tests/smoke_test.py` had a hardcoded expectation of 14
sensor cards, but `gateway/cards/` actually has 15 files - a 15th card
(`15_rs485_soil.json`, a soil moisture probe) was added at some point and
marked "PROVISIONAL, not yet confirmed" in its own notes, but the smoke
test was never updated to match.

Fix: changed that one check in `gateway/tests/smoke_test.py` to count the
actual card files on disk instead of a hardcoded number, so it can't go
stale again if a 16th card is added later. The other two places that
mention "14" were left alone - they describe how many sensor types the
simulator actually produces today (14), which is still accurate, since the
new 15th card was never wired into the simulator.

## What was tested (macOS/Linux, run directly on this machine)

| # | Check | Result |
|---|---|---|
| 1 | Fresh build: `python3 start_installation.py --recreate` - creates the environment, installs everything, runs the self-test | Passed, self-test passed, exit code 0 |
| 2 | Running it again right after - should reuse the environment instead of rebuilding it | Passed - printed "Reusing existing .venv-gateway", still succeeded |
| 3 | `python3 start_installation.py --with-anthropic` - should also install the optional package for the "bring your own API key" option | Passed - `anthropic` package confirmed installed afterward |
| 4 | `bash gateway.sh smoke` - running a gateway command with no manual "activate" step at all | Passed |
| 5 | `bash setup.sh` run directly, skipping `start_installation.py` entirely - should still work standalone | Passed |
| 6 | A simulated old Python (3.9) put first on the PATH, to confirm the "your Python is too old" message actually triggers | Correctly detected and stopped with the right message, exit code 2 |

The one-time Bluetooth permission step (Linux only) was also exercised on
every run above: since this sandbox's `sudo` requires a password and none
was available non-interactively, it correctly failed fast (no hang) and
fell back to printing the exact manual command, without failing the rest
of setup. On a student's own machine, typing a `sudo` password when
prompted would let this step complete automatically instead.

## Not yet tested (needs a real Windows machine)

- `setup.bat`, `gateway.bat`, and `start_installation.py` on Windows itself
  (Command Prompt and PowerShell)
- Behaviour when only the non-functional Microsoft Store Python placeholder
  is present
- `--recreate` / `--with-anthropic` on Windows
- The exact wording of the printed next-step commands on Windows

## Full raw output

The complete terminal output for checks 1-6 above (including all the pip
install logs) was saved during testing to a temporary scratch file, not
committed to the repo. Ask for it to be re-run if a fresh copy is needed.
