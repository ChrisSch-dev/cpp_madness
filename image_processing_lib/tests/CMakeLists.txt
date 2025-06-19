add_executable(imgproc_tests test_main.cpp)
target_link_libraries(imgproc_tests PRIVATE img_core)
add_test(NAME imgproc_tests COMMAND imgproc_tests)