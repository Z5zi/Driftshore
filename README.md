# Driftshore

Original IP subtropical open-world vertical slice for **Unreal Engine 5.8.2**. Neon nightlife, marinas, wetlands, and highway strips around the fictional port metro **Suncove**.

**Original IP — not affiliated with Rockstar.**

## What this repo is

A compile-oriented C++ scaffold: modules, game mode, third-person character stubs (Enhanced Input), a simple vehicle pawn stub, mission/objective and **Pressure** (heat) subsystems, plus design docs. Large `.uasset` / `.umap` binaries are **not** committed — create maps and content locally after generating project files.

## Requirements

- Unreal Engine **5.8.2** (Visual Studio 2022 on Windows, or matching toolchain on Linux/macOS)
- Git

## First run

1. Clone this repository.
2. Right-click `Driftshore.uproject` → **Generate Visual Studio project files** (or run the engine’s generate-project-files workflow on your platform).
3. Open `Driftshore.uproject` in UE 5.8.2.
4. Let the editor compile the `Driftshore` / `DriftshoreEditor` modules on first launch.
5. Create a World Partition map under `Content/Maps/` named `Suncove_VerticalSlice` (or update `Config/DefaultEngine.ini` to match your map path).
6. Create Enhanced Input assets under `Content/Input/` and wire them to `ADSCharacter` / `ADSPlayerController` as noted in source comments.
7. Place a player start, a stub vehicle, and a simple mission trigger for the marina district vertical slice.

## Project layout

```
Driftshore.uproject
Config/                 DefaultEngine / DefaultInput / DefaultGame
Content/                Folder stubs only (see Content/README.md)
Source/Driftshore/      Runtime C++ module
Source/DriftshoreEditor/ Editor module stub
Docs/                   Prototype plan
DESIGN.md               Pitch, pillars, systems
```

## Honesty about content

Git tracks source, config, and docs. Mesh/material/map binaries stay local (see `.gitignore`). Expect to author the marina district, characters, and UI yourself or from your own original assets.

## License / IP

Original setting and characters (Suncove, Driftshore protagonists). Do not import third-party game assets or trademarked names.
