#include "chat_client.hpp"
#include <iostream>

ChatClient::ChatClient() : socket_(io_) {}

bool ChatClient::connect(const std::string& host, unsigned short port) {
    asio::ip::tcp::resolver resolver(io_);
    asio::error_code ec;
    asio::connect(socket_, resolver.resolve(host, std::to_string(port)), ec);
    if (ec) return false;
    running_ = true;
    client_thread_ = std::thread(&ChatClient::read_loop, this);
    return true;
}
void ChatClient::send(const std::string& message) {
    asio::write(socket_, asio::buffer(message));
}
void ChatClient::set_on_message(MessageCallback cb) {
    on_message_ = cb;
}
void ChatClient::read_loop() {
    char data[1024];
    while (running_) {
        asio::error_code ec;
        size_t len = socket_.read_some(asio::buffer(data), ec);
        if (ec) break;
        if (on_message_) on_message_(std::string(data, len));
    }
}
void ChatClient::close() {
    running_ = false;
    io_.stop();
    if (client_thread_.joinable()) client_thread_.join();
}