#pragma once
#include <asio.hpp>
#include <thread>
#include <string>
#include <functional>

class ChatClient {
public:
    using MessageCallback = std::function<void(const std::string&)>;
    ChatClient();
    bool connect(const std::string& host, unsigned short port);
    void send(const std::string& message);
    void set_on_message(MessageCallback cb);
    void close();

private:
    asio::io_context io_;
    asio::ip::tcp::socket socket_;
    std::thread client_thread_;
    MessageCallback on_message_;
    bool running_ = false;
    void read_loop();
};