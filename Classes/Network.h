//
// Created by jacob on 9/14/20.
//

#ifndef SIGMAHOST_NETWORK_H
#define SIGMAHOST_NETWORK_H

#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost::asio;
using ip::tcp;

class Network {
public:
    void Initilize(); //create network object

private:
    std::string _read(tcp::socket & socket); //read a message sent from the client
    void _send(tcp::socket & socket, const std::string& message); //send a message to the client

};


#endif //SIGMAHOST_NETWORK_H
