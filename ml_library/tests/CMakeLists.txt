add_executable(ml_tests test_main.cpp)
target_link_libraries(ml_tests PRIVATE ml_core)
add_test(NAME ml_tests COMMAND ml_tests)