#include "chat_client.hpp"
#include "chat_server.hpp"
#include <iostream>
#include <thread>

int main() {
    std::cout << "Chat Application\n1. Server\n2. Client\nChoose: ";
    int mode; std::cin >> mode;
    if (mode == 1) {
        ChatServer server(12345);
        server.start();
        std::cout << "Server running. Press Enter to exit.\n";
        std::cin.ignore(); std::cin.get();
        server.stop();
    } else {
        ChatClient client;
        std::string host = "127.0.0.1";
        client.connect(host, 12345);
        client.set_on_message([](const std::string& msg) {
            std::cout << ">> " << msg << std::endl;
        });
        std::string msg;
        std::cin.ignore();
        while (std::getline(std::cin, msg)) {
            client.send(msg);
        }
        client.close();
    }
}