find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
add_executable(snake_game_gui main.cpp gamewindow.cpp)
target_link_libraries(snake_game_gui PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)