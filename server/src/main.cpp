#include <iostream>
#include <fstream>
#include "connection/Server.h"


int main() {
    std::cout << "Start!" << std::endl;

    try
    {
        boost::asio::io_service io_service;
        Server server(io_service, 12000);

        server.bind_command("kek", []{
            std::ofstream f("test.txt");
            f << "kek";
            f.close();
        });

        server.start();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
