# File Compression Tool (C++)

Huffman coding based file compressor/decompressor with GUI and CLI.

## Features
- Compress/decompress files (Huffman)
- CLI and ImGui-based GUI
- Compression statistics and logs
- Batch compression (GUI)
- Drag & drop (GUI)

## Build
```bash
mkdir build && cd build
cmake ..
make
```

## Run
- **CLI:** `./compressor`
- **GUI:** `./compressor_gui`

## Dependencies
- C++17+
- [ImGui](https://github.com/ocornut/imgui) + [SFML](https://github.com/SFML/SFML) (for GUI)

## Folder structure
- `src/` — core logic
- `gui/` — ImGui interface
- `tests/` — unit tests