add_executable(compressor_tests test_compress.cpp)
target_link_libraries(compressor_tests PRIVATE compressor_core)
add_test(NAME compressor_tests COMMAND compressor_tests)