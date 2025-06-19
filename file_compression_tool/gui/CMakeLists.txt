find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_executable(compressor_gui main.cpp imgui_wrap.cpp)
target_link_libraries(compressor_gui PRIVATE compressor_core sfml-graphics sfml-window sfml-system)