find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(chat_gui main_imgui.cpp imgui_impl.cpp)
target_include_directories(chat_gui PRIVATE ../src .)
target_link_libraries(chat_gui PRIVATE chat_core sfml-graphics sfml-window sfml-system)