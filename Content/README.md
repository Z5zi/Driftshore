# Content layout (local authoring)

Large `.uasset` / `.umap` files are gitignored. Create assets in Unreal Editor 5.8.2 under these folders. Seed textures / heightmap / HDRI live on Hugging Face — see `Docs/ASSETS_HF.md`.

```
Content/
  Maps/                    Suncove_VerticalSlice (World Partition), lighting sublevels
  Environment/
    Pierline/              Marina district blockout, docks, neon façades, slips
    Shared/                Reusable coastal props, railings, signage kits
  Materials/               Master materials + instances (asphalt, pier wood, metal, neon)
  Characters/              Maren Quill / Theo “Rook” Varela meshes, anim BPs
  Vehicles/                Marina runabout / compact coupe stubs
  Audio/                   Marina ambient, neon night bed, Pressure radio chatter
  UI/                      Pressure meter, objective text, mission summary
  Input/                   IMC + IA_* Enhanced Input assets
  Data/                    CSV/JSON environment tables (tracked in git)
```

Placeholder note: until maps exist, DefaultEngine.ini may warn about missing `Suncove_VerticalSlice` — create it on first editor open with World Partition enabled.
