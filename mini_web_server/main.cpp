#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <asio.hpp>
#include <filesystem>

using asio::ip::tcp;

void handle_client(tcp::socket socket) {
    try {
        char buffer[8192];
        size_t len = socket.read_some(asio::buffer(buffer));
        std::istringstream req(std::string(buffer, len));
        std::string method, path, version;
        req >> method >> path >> version;
        if (path == "/") path = "/index.html";
        std::string file_path = "." + path;
        std::ostringstream ss;
        if (method == "GET" && std::filesystem::exists(file_path)) {
            std::ifstream file(file_path, std::ios::binary);
            ss << "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" << file.rdbuf();
        } else if (method == "POST") {
            ss << "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPOST received";
        } else {
            ss << "HTTP/1.1 404 Not Found\r\n\r\nFile Not Found";
        }
        asio::write(socket, asio::buffer(ss.str()));
    } catch (...) {}
}

int main() {
    asio::io_context io;
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8080));
    std::cout << "Serving on http://localhost:8080/\n";
    while (true) {
        tcp::socket socket(io);
        acceptor.accept(socket);
        std::thread(handle_client, std::move(socket)).detach();
    }
}