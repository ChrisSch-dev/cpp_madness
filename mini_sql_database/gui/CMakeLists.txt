find_package(Qt6 COMPONENTS Widgets REQUIRED)
add_executable(mini_sql_gui mainwindow.cpp main.cpp)
target_link_libraries(mini_sql_gui PRIVATE sql_core Qt6::Widgets)