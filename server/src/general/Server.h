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
    void handle_accept(ConnectionHandler::Ptr connection, const boost::system::error_code& err);
    void resolve(std::string data) override;
    void resolve_error(const boost::system::error_code &error) override;
private:
    std::string read(tcp::socket socket);
    void send(tcp::socket socket, const std::string& message);
    void start_accept();

    io_service& m_service;
    tcp::acceptor m_acceptor;
    std::mutex m_mutex;
};


#endif // SERVER_H
