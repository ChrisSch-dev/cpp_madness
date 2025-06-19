find_package(Qt6 COMPONENTS Widgets REQUIRED)
add_executable(ml_tool_gui mainwindow.cpp main.cpp)
target_link_libraries(ml_tool_gui PRIVATE ml_core Qt6::Widgets)