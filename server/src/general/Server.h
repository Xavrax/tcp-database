#ifndef SERVER_H
#define SERVER_H

#include "IDataResolver.h"
#include "ConnectionHandler.h"
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;

class Server : public IDataResolver {
public:
    explicit Server(boost::asio::io_service& io_service, int port) noexcept;

    void start();
    void handle_accept(const ConnectionHandler::Ptr& connection, const boost::system::error_code& err);
    void bind_command(const std::string& command, std::function<void()> function);
    void resolve(std::string data) override;
    void resolve_error(const boost::system::error_code &error) override;
private:
    std::string read(tcp::socket socket);
    void send(tcp::socket socket, const std::string& message);
    void start_accept();

    io_service& m_service;
    tcp::acceptor m_acceptor;
    std::mutex m_mutex;
    // todo: change with lib creation
    std::unordered_map<std::string, std::function<void()>> m_functionalities;
};


#endif // SERVER_H
