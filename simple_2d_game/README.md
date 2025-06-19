# Simple 2D Snake Game (C++)

Console and GUI (SFML) versions of Snake, with high scores.

## Features
- Console & GUI (SFML) versions
- Pause/resume, high score save/load
- Multiple levels, increasing speed (GUI)
- Sound and graphics (GUI)
- Configurable controls

## Build
```bash
mkdir build && cd build
cmake ..
make
```

## Run
- **Console:** `./snake_game`
- **GUI:** `./snake_game_gui`

## Dependencies
- C++17+
- [SFML 2.6+](https://www.sfml-dev.org/) (for GUI)

## Folder structure
- `src/` — game logic, console
- `gui/` — SFML graphics/sound
- `tests/` — unit tests