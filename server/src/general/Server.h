#ifndef SERVER_H
#define SERVER_H

#include "ServerParams.h"

class Server {
public:
    explicit Server(const ServerParams& params) noexcept;

private:
    std::string m_ip;
    int m_port;
    int m_max_message_length;
    short m_max_connections;
};


#endif // SERVER_H
