# Pierline Marina — Vertical Slice Environment Breakdown

Original Suncove district. Not affiliated with any third-party open-world franchise.

## Intent

Deliver a **walkable + short driveable loop** for Weeks 1–2: Slip B pickup → Neon Quay corridor → Pier 9 warehouse alley drop, with readable day/night contrast and diegetic **Pressure** feedback.

## Block plan (greybox first)

| Block | Approx size | Contents |
|-------|-------------|----------|
| **Slips A–C** | ~80 × 60 m | Three pier fingers, player start at Slip B, tied runabout at Slip A |
| **Neon Quay** | ~100 × 40 m | Tourist boardwalk, Tideglass Bar, bait shop, neon façades |
| **Pier 9 Yard** | ~70 × 50 m | Warehouse, delivery alley, low loading dock |
| **Harbor Spine** | ~150 × 20 m | Connector road between quay and causeway exit east |
| **Water apron** | surrounding | Simple water plane + collision; no swim sim in slice |

World Partition: keep streaming cells ~64–128 m so the marina loads as 2–4 cells.

## Landmarks (original names)

1. **Neon Quay** — nightlife face of the marina; magenta/cyan emissives.
2. **Slip B** — mission crate spawn; Maren’s Week-1 start.
3. **Pier 9 Warehouse Alley** — drop-off; tight for vehicles.
4. **Tideglass Bar** — Rook contact flavor; interior optional stub.
5. **Harbor Master Booth** — overlook + Pressure radio source.

## Lighting mood

| Preset id | Mood |
|-----------|------|
| `pierline_dawn` | Soft gold, wet boards, low neon |
| `pierline_noon` | Harsh subtropical contrast |
| `pierline_golden` | Long warm shadows; neon waking |
| `pierline_neon_night` | Humid fog, neon dominant, Pressure chatter louder |

Use HF HDRI `klippad_sunrise_1_1k.hdr` as dawn reference only (CC0 Poly Haven). Author Directional + Sky Light + Exponential Height Fog + Post Process volumes in-editor to match `Content/Data/lighting_presets.json`.

## Traffic / pedestrian density notes

Profile: `marina_tourist` (`Content/Data/traffic_density.json`).

- **Day (noon):** light foot traffic on boardwalk; few static boats.
- **Neon night:** highest pedestrian density; keep AI as stub volumes / animated placeholders in prototype.
- **Vehicles:** 1 driveable runabout + a few static parked props; no full traffic sim in Week 2.
- **Patrol stub:** one trigger volume near Neon Quay that spikes Pressure on vehicle collision / loud entry.

Mangrove Reach (west) and Causeway Strip (east) exist as **exit teasers** only — greybox stubs optional, not required for slice exit criteria.

## Props & materials

See `Content/Data/props_catalog.json` and HF `props_manifest.json`. Prefer pier wood, worn concrete, dock metal, asphalt, and emissive neon masters.

## Mission geography — Pier 9 Drop

```
[Player Start / Slip B] --boardwalk--> [Neon Quay] --spine--> [Pier 9 Alley]
         ^ crate pickup                                      ^ delivery
```

Silent path hugs the water edge (lower pedestrian volumes). Loud path cuts Neon Quay center (patrol stub).

## Out of scope for this district slice

City-wide schedules, swimming traversal, multiplayer, licensed music, or any third-party IP architecture lookalikes.
