# Driftshore — Prototype Plan (Weeks 1–2)

## Goals

Ship a playable **Pierline Marina** vertical slice: third-person on-foot, one simple vehicle, one mission (“Pier 9 Drop”), and a visible **Pressure** meter stub.

## Week 1 — Foundations

| Day | Milestone |
|-----|-----------|
| 1 | Generate project files; confirm `Driftshore` module compiles; empty World Partition map `Suncove_VerticalSlice`. |
| 2 | `ADSCharacter` + Enhanced Input (Move/Look/Jump/Sprint); spawn at Pierline player start. |
| 3 | Camera boom polish; Interact trace; simple UI widget placeholder for Pressure + objective text. |
| 4 | Blockout Pierline Marina (docks, 2–3 neon façades, slip B, alley drop point) with greybox meshes. |
| 5 | `ADSVehiclePawn` enter/exit; drive a short marina loop without falling through water collision. |

**Week 1 exit:** Walk, drive, and stand at slip B / alley with debug HUD.

## Week 2 — Mission + Pressure

| Day | Milestone |
|-----|-----------|
| 1 | `UDSMissionSubsystem`: start/complete “Pier 9 Drop”; objective markers on slip + alley. |
| 2 | `UDSPressureSubsystem`: gain/decay API; 3 tiers; debug on-screen tier. |
| 3 | Mission hooks: crate pickup raises Pressure slightly; collision with stub patrol volume spikes Pressure. |
| 4 | Score summary (time, max Pressure, silent bonus); restart flow from Game Mode. |
| 5 | Pass review: 5-minute playable loop; fix blockers; tag `prototype-w2` on git. |

**Week 2 exit:** One complete mission loop with Pressure feedback and a score readout.

## Risks & notes

- Keep Content binaries out of git; share via LFS or internal storage later if needed.
- Prefer stub AI (trigger volumes) over full NPC brains in Week 2.
- Do not introduce third-party franchise names, assets, or lookalike branding.
