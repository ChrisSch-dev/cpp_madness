#include "chat_server.hpp"
#include <iostream>

ChatServer::ChatServer(unsigned short port)
    : acceptor_(io_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{}

void ChatServer::start() {
    running_ = true;
    server_thread_ = std::thread(&ChatServer::accept_loop, this);
}

void ChatServer::accept_loop() {
    while (running_) {
        auto socket = std::make_shared<asio::ip::tcp::socket>(io_);
        acceptor_.accept(*socket);
        clients_.push_back(socket);
        std::thread([this, socket]() {
            try {
                char data[1024];
                while (true) {
                    size_t len = socket->read_some(asio::buffer(data));
                    std::string msg(data, len);
                    broadcast(msg);
                }
            } catch (...) {
                // Remove client
            }
        }).detach();
    }
}

void ChatServer::broadcast(const std::string& message) {
    for (auto& sock : clients_) {
        asio::write(*sock, asio::buffer(message));
    }
}

void ChatServer::stop() {
    running_ = false;
    io_.stop();
    if (server_thread_.joinable()) server_thread_.join();
}