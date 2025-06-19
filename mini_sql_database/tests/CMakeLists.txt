add_executable(sql_tests test_main.cpp)
target_link_libraries(sql_tests PRIVATE sql_core)
add_test(NAME sql_tests COMMAND sql_tests)