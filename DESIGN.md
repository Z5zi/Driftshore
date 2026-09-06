# Driftshore — Design Document

## Pitch

**Driftshore** is a third-person open-world vertical slice set in **Suncove**, a fictional subtropical port metro and its chain of keys. Neon nightlife bleeds into marina boards, mangrove wetlands, and sun-bleached highway strips. Players bounce between on-foot exploration and light vehicle play while a rising **Pressure** meter tracks how hot the streets run after loud jobs.

Original IP — not affiliated with Rockstar or any existing open-world franchise.

## Pillars

1. **Coastal contrast** — Bright day docks vs. humid neon night; wetlands hush vs. strip roar.
2. **Readable Pressure** — Heat is visible, fair, and diegetic (radio chatter, drones, checkpoint density), never a copy of another title’s Wanted UI.
3. **Tight vertical slice** — One small district playable end-to-end before world expansion.
4. **Original voices** — Protagonists with their own history in Suncove; no borrowed names or lore.

## Setting: Suncove

A mid-size subtropical port on a crescent bay. Cargo cranes, tourist marinas, inland wetlands, and a ribbon of state highway that links the keys. Economy mixes shipping, nightlife tourism, and grey-market boat runs at dusk.

## Protagonists

### Maren Quill
Former harbor pilot who lost her license after a night collision covered up by a shipping consortium. Knows every channel marker and blind dock in Suncove. Motivated to clear her name — and to keep her younger sibling out of the marina’s debt crews.

### Theo “Rook” Varela
Street mechanic turned courier for off-book marina jobs. Grew up in the wetlands trailer parks north of the causeway. Charming under pressure, better with engines than with people who ask too many questions. Wants one clean score to buy a legitimate shop lease on Pier 9.

Either character can be the Week-1 playable; the other appears as a mission contact in the slice.

## Districts (3–5)

| District | Flavor | Slice role |
|----------|--------|------------|
| **Pierline Marina** | Tourist docks, neon bars, boat slips | **Vertical slice hub** — start, vehicle, first mission |
| **Causeway Strip** | Highway, motels, fuel plazas | Transit + light chase sandbox |
| **Mangrove Reach** | Wetlands, raised walkways, quiet crime | Stealth / low-Pressure routes |
| **Glass Harbor** | Downtown glass towers, night markets | Mid-game density (post-slice) |
| **Outer Keys** | Sparse islands, radio towers | Endgame / smuggling lanes (post-slice) |

## Systems

### Movement & camera
Third-person on-foot: walk / sprint / jump, cover-friendly camera boom, soft collision on marina rails. Enhanced Input for Move, Look, Jump, Sprint, Interact, EnterVehicle, MissionPing.

### Vehicles
Simple driveable pawn (marina runabout or compact coupe stub). Enter/exit via Interact. No deep simulation in the prototype — acceleration, steering, brake, and a handbrake enough for a short Pierline loop.

### Pressure (heat)
Original naming: **Pressure**. Builds from loud crimes, vehicle collisions with patrols, and mission fails. Decays in wetlands and quiet interiors. Escalation tiers change ambient chatter and spawn checkpoint density — implemented as `UDSPressureSubsystem` stub.

### Missions / objectives
`UDSMissionSubsystem` tracks active objective, score hook (time / noise / cash), and completion. Vertical slice hook: **“Pier 9 Drop”** — pick up a sealed crate at slip B, deliver to a warehouse alley before Pressure hits tier 2.

### Score hook
Optional bonus for silent delivery (Pressure stays ≤ 1) or fast delivery under a soft timer. Displayed as a simple end-of-mission summary, not a full GTA-style star system.

## Pierline Marina (vertical slice environment)

Detailed block plan, landmarks, lighting mood, and traffic density notes live in **`Docs/PIERLINE_MARINA.md`**.

Data-driven tables (districts, spawns, POIs, props, lighting presets, traffic profiles): **`Content/Data/`**.

Binary texture / terrain / HDRI seeds: Hugging Face dataset **Reticule/Driftshore-assets** — see **`Docs/ASSETS_HF.md`**.

### Quick landmark list
- Neon Quay, Slip B, Pier 9 Warehouse Alley, Tideglass Bar, Harbor Master Booth

### Lighting presets (ids)
`pierline_dawn`, `pierline_noon`, `pierline_golden`, `pierline_neon_night`

## Out of scope (prototype)

Full multiplayer, deep RPG progression, licensed music, city-wide AI schedules, or any third-party IP assets.
