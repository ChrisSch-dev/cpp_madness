# Mini SQL Database (C++)

Tiny SQL-like database engine with persistence, CLI, and GUI (Qt).

## Features
- Supports SELECT, INSERT, UPDATE, DELETE
- WHERE and ORDER BY (basic)
- Persistence (save/load)
- Command-line and GUI (Qt) query console
- Table browser (GUI)

## Build
```bash
mkdir build && cd build
cmake ..
make
```

## Run
- **CLI:** `./mini_sql`
- **GUI:** `./mini_sql_gui`

## Dependencies
- C++17+
- [Qt 6](https://www.qt.io/) (for GUI)

## Folder structure
- `src/` — SQL interpreter/engine
- `gui/` — Qt GUI
- `tests/` — tests
- `data/` — saved tables