# Driftshore assets on Hugging Face

Large binary seeds (textures, heightmap, HDRI) are **not** stored in GitHub. They live in the public dataset:

**https://huggingface.co/datasets/Reticule/Driftshore-assets**

## Pull

```bash
# Requires huggingface_hub / hf CLI and (optional) HF_TOKEN for higher rate limits
hf download Reticule/Driftshore-assets --repo-type dataset --local-dir ./Driftshore-assets
```

Or with Python:

```bash
huggingface-cli download Reticule/Driftshore-assets --repo-type dataset --local-dir ./Driftshore-assets
```

## Pack layout

```
Driftshore-assets/
  README.md
  terrain/pierline_marina_heightmap_1024.png
  textures/asphalt_02/…
  textures/concrete_floor_worn_001/…
  textures/wood_planks_grey/…
  textures/metal_plate/…
  hdri/klippad_sunrise_1_1k.hdr
  manifests/props_manifest.json
  licenses/LICENSES.md
```

## Import into Unreal Engine 5.8.2

1. Copy (or symlink) pulled folders into `Content/` mirrors, e.g.:
   - `textures/*` → import under `Content/Materials/Textures/`
   - `terrain/pierline_marina_heightmap_1024.png` → Landscape import on `Suncove_VerticalSlice`
   - `hdri/klippad_sunrise_1_1k.hdr` → HDRI Backdrop / Sky Light cubemap test
2. Create material instances documented in `Content/Materials/README.md`.
3. Do **not** commit resulting `.uasset` files (gitignored). Keep the HF dataset as the source of truth for binaries.

## Licensing

Poly Haven textures and HDRI are **CC0**. See `licenses/LICENSES.md` inside the dataset. Procedural heightmap is original Driftshore seed data (Z5zi). Do not mix in ripped game assets.
