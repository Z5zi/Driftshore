# Data-driven environment tables

CSV/JSON consumed by designers and future data assets. Not `.uasset` binaries.

| File | Purpose |
|------|---------|
| `districts.json` | District ids, bounds hints, Pressure bias |
| `spawn_points.csv` | Player / vehicle / mission spawns |
| `pois.json` | Points of interest + interact tags |
| `props_catalog.json` | Intended prop categories for Pierline |
| `lighting_presets.json` | Time-of-day mood presets |
| `traffic_density.json` | Vehicle / pedestrian density by district & TOD |

C++ stubs (`FDSTrafficDensityConfig`, `ADSPoiActor`, etc.) mirror these fields for later DataTable import.
