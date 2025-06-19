# Mini Web Server (C++)

A basic HTTP 1.1 server with file serving and REST API support. Console and GUI (Qt) admin.

## Features
- Serve static files from `www/`
- Multi-threaded
- Simple REST API (GET/POST)
- Basic access logs
- GUI dashboard (Qt) for monitoring, logs, config

## Build
```bash
mkdir build && cd build
cmake ..
make
```

## Run
- **Server:** `./web_server`
- **GUI:** `./web_server_gui`

## Dependencies
- C++17+
- [Qt 6](https://www.qt.io/) (for GUI)
- [Asio](https://think-async.com/Asio/) (header-only)

## Folder structure
- `src/` — HTTP server, REST API
- `gui/` — Qt admin dashboard
- `tests/` — tests
- `www/` — static files