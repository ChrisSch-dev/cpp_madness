cmake_minimum_required(VERSION 3.16)
project(chat_application)

set(CMAKE_CXX_STANDARD 17)

# Core chat logic
add_library(chat_core STATIC
    src/chat_client.cpp
    src/chat_server.cpp
)

target_include_directories(chat_core PUBLIC src)

# Console App
add_executable(chat_console src/main.cpp)
target_link_libraries(chat_console PRIVATE chat_core)

# ImGui + SFML GUI App
add_subdirectory(gui)