//
// Created by jacob on 9/14/20.
//

#ifndef SIGMAHOST_NETWORK_H
#define SIGMAHOST_NETWORK_H

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include "Message.h"

using namespace boost::asio;
using ip::tcp;

class Network {
public:
    void Run(); //create network object

private:
    bool erState = false;
    std::string _read(tcp::socket & socket); //read a message sent from the client
    static void _send(tcp::socket & socket, const std::string& message); //send a message to the client
    bool _verifyHelloMessage(tcp::socket& socket, std::string inMessage); //verify that the message is in a valid Hello form
    void _sendProperResponse(tcp::socket& socket, std::string& recievedMsg); //formulate a proper response to a message recieved
    bool _processMessage(tcp::socket& socket, std::string inMessage); //process the message recieved from the client -- will return false if the message is not valid
    void _processRequest(tcp::socket& socket); //handle the request that has been recieved
    void _timeRqst(); //handle the request for the system time
};

#endif //SIGMAHOST_NETWORK_H
