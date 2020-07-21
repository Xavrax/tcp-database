#include <iostream>

#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

int main() {
    std::cout << "Hello, World!" << std::endl;


    boost::asio::io_service io_service;
//socket creation
    tcp::socket socket(io_service);
//connection
    socket.connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 12000 ));
// request/message from client
    const string msg = "kek\n";
    boost::system::error_code error;
    boost::asio::write( socket, boost::asio::buffer(msg), error );
    if( !error ) {
        cout << "Client sent hello message!" << endl;
    }
    else {
        cout << "send failed: " << error.message() << endl;
    }

    return 0;
}
