# BESS C reference implementation

This directory contains a portable, deterministic C11 reference implementation organized by production feature. It deliberately keeps hardware and network adapters outside the safety core: BMS/PCS drivers should call the validated control APIs after applying site-specific limits.

## Build and checks

```sh
make check
make
```

The check target uses strict compiler warnings (`-Wall -Wextra -Werror -Wpedantic -Wconversion -Wshadow`).

## Modules

- `bess_safety.c`: limit validation and fail-safe power approval
- `bess_control.c`: operating modes and charge/discharge commands
- `bess_alarm.c`: bounded alarm lifecycle store
- `bess_telemetry.c`: bounded telemetry history and CSV export
- `bess_grid.c`: frequency/voltage support command calculation
- `bess_ems.c`: peak shaving, renewable absorption, and reserve-aware dispatch
- `bess_auth.c`: role-based authorization decisions
- `bess_maintenance.c`: service and throughput tracking

This software is a control-domain reference and is not a substitute for certified BMS, PCS, protection, fire, or emergency-stop hardware. Site commissioning must verify applicable utility, safety, cybersecurity, and jurisdictional requirements.
