#pragma once
#include <asio.hpp>
#include <thread>
#include <vector>
#include <memory>
#include <string>

class ChatServer {
public:
    ChatServer(unsigned short port);
    void start();
    void stop();
    void broadcast(const std::string& message);
private:
    asio::io_context io_;
    asio::ip::tcp::acceptor acceptor_;
    std::vector<std::shared_ptr<asio::ip::tcp::socket>> clients_;
    std::thread server_thread_;
    bool running_ = false;
    void accept_loop();
};