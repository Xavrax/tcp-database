#include <iostream>
#include "general/Server.h"


int main() {
    std::cout << "Start!" << std::endl;

    try
    {
        boost::asio::io_service io_service;
        Server server(io_service, 12000);
        server.start();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
