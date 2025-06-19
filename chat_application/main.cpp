#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <map>
#include <asio.hpp>

// Compile with: g++ main.cpp -pthread -I/path/to/asio/include

using asio::ip::tcp;
std::mutex cout_mutex;

void handle_client(tcp::socket socket, int id, std::map<int, tcp::socket*>& clients, std::mutex& clients_mutex) {
    try {
        char data[1024];
        while (true) {
            size_t length = socket.read_some(asio::buffer(data));
            std::lock_guard<std::mutex> lock(clients_mutex);
            for (auto& c : clients) {
                if (c.first != id)
                    asio::write(*c.second, asio::buffer(data, length));
            }
        }
    } catch (...) {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Client " << id << " disconnected.\n";
    }
}

void run_server() {
    asio::io_context io;
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 12345));
    std::map<int, tcp::socket*> clients;
    std::mutex clients_mutex;
    int id = 0;
    std::vector<std::thread> threads;

    std::cout << "Server started on port 12345\n";
    while (true) {
        auto* socket = new tcp::socket(io);
        acceptor.accept(*socket);
        {
            std::lock_guard<std::mutex> lock(clients_mutex);
            clients[id] = socket;
        }
        std::cout << "Client " << id << " connected\n";
        threads.emplace_back(handle_client, std::move(*socket), id, std::ref(clients), std::ref(clients_mutex));
        id++;
    }
    for (auto& t : threads) t.join();
}

void run_client() {
    asio::io_context io;
    tcp::resolver resolver(io);
    tcp::socket socket(io);
    asio::connect(socket, resolver.resolve("127.0.0.1", "12345"));
    std::cout << "Connected! Type messages:\n";

    std::thread reader([&](){
        char data[1024];
        while (true) {
            asio::error_code ec;
            size_t len = socket.read_some(asio::buffer(data), ec);
            if (ec) break;
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "\n[Peer] " << std::string(data, len) << "\n> ";
            std::cout.flush();
        }
    });

    std::string msg;
    while (std::getline(std::cin, msg)) {
        asio::write(socket, asio::buffer(msg));
        std::cout << "> ";
    }
    reader.join();
}

int main() {
    std::cout << "Chat Application\n1. Server\n2. Client\nChoose: ";
    int mode; std::cin >> mode;
    std::cin.ignore();
    if (mode == 1) run_server();
    else run_client();
}