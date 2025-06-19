# Image Processing Library (C++)

Simple image processing for PGM/JPG/PNG, with CLI and GUI (Qt or ImGui).

## Features
- Grayscale, invert, blur, resize, crop
- Batch processing (GUI)
- Load/save JPG, PNG, PGM
- Drag & drop interface (GUI)
- Histogram (GUI)

## Build
```bash
mkdir build && cd build
cmake ..
make
```

## Run
- **CLI:** `./imgproc`
- **GUI:** `./imgproc_gui`

## Dependencies
- C++17+
- [Qt 6](https://www.qt.io/) or ImGui+SFML (for GUI)
- [stb_image](https://github.com/nothings/stb) (header-only, for image IO)

## Folder structure
- `src/` — image ops
- `gui/` — Qt or ImGui GUI
- `tests/` — tests
- `images/` — test images