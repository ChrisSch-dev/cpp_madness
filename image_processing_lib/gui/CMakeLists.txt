find_package(Qt6 COMPONENTS Widgets REQUIRED)
add_executable(imgproc_gui mainwindow.cpp main.cpp)
target_link_libraries(imgproc_gui PRIVATE img_core Qt6::Widgets)