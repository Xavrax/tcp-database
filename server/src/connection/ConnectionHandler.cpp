#include "ConnectionHandler.h"

ConnectionHandler::ConnectionHandler(boost::asio::io_service &service, IDataResolver &resolver) noexcept :
        m_socket(service),
        m_resolver(resolver) {

}

tcp::socket &ConnectionHandler::get_socket() {
    return m_socket;
}

void ConnectionHandler::start() {
    m_socket.async_read_some(
        boost::asio::buffer(m_buffer, m_buffer_size),
        boost::bind(
                &ConnectionHandler::handle_read,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
        )
    );

    m_socket.async_write_some(
            boost::asio::buffer(m_buffer, m_buffer_size),
            boost::bind(
                    &ConnectionHandler::handle_write,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
            )
    );
}

void ConnectionHandler::handle_read(const boost::system::error_code &error, size_t) {
    if (!error) {
        m_resolver.resolve(m_buffer);
    } else {
        m_resolver.resolve_error(error);
        m_socket.close();
    }
}

void ConnectionHandler::handle_write(const boost::system::error_code &error, size_t) {
    if (error) {
        m_resolver.resolve_error(error);
        m_socket.close();
    }
}

boost::shared_ptr<ConnectionHandler> ConnectionHandler::create(boost::asio::io_service &io_service, IDataResolver &resolver) {
    return Ptr(new ConnectionHandler(io_service, resolver));
}

