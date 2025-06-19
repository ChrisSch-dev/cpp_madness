# ML Library (C++)

Tiny ML toolkit with regression, k-means, and a GUI (ImGui or Qt).

## Features
- Linear regression, K-means clustering
- Load CSV, train/test
- GUI for plotting (ImGui or Qt)
- Save/load models
- CLI and GUI

## Build
```bash
mkdir build && cd build
cmake ..
make
```

## Run
- **CLI:** `./ml_tool`
- **GUI:** `./ml_tool_gui`

## Dependencies
- C++17+
- [ImGui](https://github.com/ocornut/imgui) or Qt 6 (for GUI)
- [matplotlib-cpp](https://github.com/lava/matplotlib-cpp) for plotting (optional)

## Folder structure
- `src/` — ML algorithms
- `gui/` — GUI/plotting code
- `tests/` — tests
- `models/` — saved models
- `datasets/` — CSVs for demo