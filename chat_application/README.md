# Chat Application (C++/ImGui/SFML/Asio)

- Supports both console & ImGui-based GUI chat
- Simple TCP server; connect multiple clients
- Uses Asio (header-only) for networking
- GUI: ImGui + SFML

## Build

```bash
git clone ...
cd chat_application
mkdir build && cd build
cmake ..
make
```

## Run

- **Server (console):** `./chat_console` and choose Server
- **Client (console):** `./chat_console` and choose Client
- **ImGui Client:** `./chat_gui`

## Dependencies

- C++17+
- [SFML](https://www.sfml-dev.org/) (`apt install libsfml-dev` or via vcpkg)
- [ImGui](https://github.com/ocornut/imgui) + [imgui-sfml](https://github.com/eliasdaler/imgui-sfml)
- [Asio standalone](https://think-async.com/Asio/)

## Features

- Multi-user chat
- Console and GUI (ImGui)
- Message list, connect/disconnect in GUI
- Extendable for rooms, usernames, etc

---

**Want the next project?**  
If you’re happy with this structure, I’ll proceed to the next: **2D Snake Game (ImGui/SFML version)**.  
Let me know if you need full source for any ImGui integration, or instructions for dependencies!
