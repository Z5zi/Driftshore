# Content layout (local authoring)

Large `.uasset` / `.umap` files are gitignored. Create these folders’ assets in the Unreal Editor:

```
Content/
  Maps/           Suncove_VerticalSlice (World Partition), lighting levels
  Characters/     Maren / Rook meshes, anim BPs, ABPs
  Vehicles/       Marina runabout or coupe stub
  UI/             Pressure meter, objective text, mission summary
  Audio/          Ambient marina, neon night bed, UI beeps
  Input/          IMC + IA_* Enhanced Input assets (create in-editor)
```

Placeholder note: until maps exist, DefaultEngine.ini may warn about missing `Suncove_VerticalSlice` — create it on first editor open.
