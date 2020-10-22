#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include "Classes/tcp_server.h"

int main() {
    //boost::asio::io_context io_context;
    //_network.initilize();
    //Network _network;
    //_network.Run();
    //return 0;

    try
    {
        boost::asio::io_context io_context;
        tcp_server server(io_context);
        io_context.run();
    }catch(std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    return 0;
    //boost.asio might be a library that we can try
}
