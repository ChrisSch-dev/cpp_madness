add_library(server_core STATIC server.cpp http.cpp main.cpp)
target_include_directories(server_core PUBLIC /path/to/asio/include)