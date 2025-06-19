find_package(Qt6 COMPONENTS Widgets REQUIRED)
add_executable(web_server_gui mainwindow.cpp main.cpp)
target_link_libraries(web_server_gui PRIVATE server_core Qt6::Widgets)