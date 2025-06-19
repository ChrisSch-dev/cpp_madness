add_library(img_core STATIC image.cpp ops.cpp main.cpp)
target_include_directories(img_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../external/stb)