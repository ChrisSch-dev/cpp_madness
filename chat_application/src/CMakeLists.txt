add_library(chat_core STATIC main.cpp server.cpp client.cpp model.cpp)
target_include_directories(chat_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} /path/to/asio/include)