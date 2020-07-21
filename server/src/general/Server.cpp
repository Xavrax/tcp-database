#include "Server.h"

Server::Server(const ServerParams& params) noexcept :
        m_ip(params.ip_address),
        m_port(params.port),
        m_max_message_length(params.max_message_length),
        m_max_connections(params.max_connections) {

}
