#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "IDataResolver.h"

using namespace boost::asio;
using ip::tcp;

class ConnectionHandler : public boost::enable_shared_from_this<ConnectionHandler> {
public:
    typedef boost::shared_ptr<ConnectionHandler> Ptr;

    ConnectionHandler(boost::asio::io_service& service, IDataResolver &resolver) noexcept;

    tcp::socket& get_socket();
    void start();
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
    void handle_write(const boost::system::error_code& error, size_t bytes_transferred);

    static Ptr create(boost::asio::io_service& io_service, IDataResolver &resolver);
private:
    tcp::socket m_socket;
    IDataResolver &m_resolver;
    enum { m_buffer_size = 1024 };
    char m_buffer[m_buffer_size];
};


#endif //CONNECTIONHANDLER_H
