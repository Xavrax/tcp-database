#ifndef SERVERPARAMS_H
#define SERVERPARAMS_H

#include <string>

struct ServerParams{
    std::string ip_address;
    int port;
    int max_message_length;
    short max_connections {10};
};

#endif //SERVERPARAMS_H
