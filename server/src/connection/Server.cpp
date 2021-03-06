#include "Server.h"
#include "ConnectionHandler.h"
#include <boost/asio.hpp>
#include <iostream>

namespace {
    const auto new_line = "\n";
}

Server::Server(boost::asio::io_service& io_service, int port) noexcept :
        m_service(io_service),
        m_acceptor(m_service, tcp::endpoint(tcp::v4(), port)) {

}

void Server::start() {
    start_accept();
    m_service.run();
}

std::string Server::read(tcp::socket socket) {
    boost::asio::streambuf buffer;
    boost::asio::read_until(socket, buffer, new_line);
    auto data = boost::asio::buffer_cast<const char*>(buffer.data());

    return data;
}

void Server::send(tcp::socket socket, const std::string& message) {
    const auto terminated_message = message + new_line;
    boost::asio::write(socket, boost::asio::buffer(terminated_message));
}

void Server::resolve(std::string data) {
    const std::lock_guard<std::mutex> lock(m_mutex);
    std::string key = data;

    if (!key.empty()) {
        key.pop_back();
    } else {
        std::cerr << "Error: Received empty request!" << std::endl;
    }

    if (m_functionalities.find(key) != m_functionalities.end()) {
        std::cout << "Executing command: " << key << std::endl;
        m_functionalities.at(key)();
    } else {
        std::cerr << "Error: Client sent unknown request: " << data << std::endl;
    }
}

void Server::resolve_error(const boost::system::error_code &error) {
    const std::lock_guard<std::mutex> lock(m_mutex);

    std::cerr << "Error: " << error.message() << std::endl;
}

void Server::start_accept() {
    ConnectionHandler::Ptr connection = ConnectionHandler::create(m_service, *this);

    m_acceptor.async_accept(
            connection->get_socket(),
            boost::bind(
                    &Server::handle_accept,
                    this,
                    connection,
                    boost::asio::placeholders::error
            )
    );
}

void Server::handle_accept(const ConnectionHandler::Ptr& connection, const boost::system::error_code &error) {
    if (!error) {
        connection->start();
    }
    start_accept();
}

void Server::bind_command(const std::string& command, std::function<void()> function) {
    m_functionalities.emplace(command, function);
}
