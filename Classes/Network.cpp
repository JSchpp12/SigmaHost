//
// Created by jacob on 9/14/20.
//
#include "Network.h"

void Network::initilize() {
    boost::asio::io_service io_service;

    //create socket connection
    tcp::socket socket(io_service);

    //listen for new connection
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 11000));

    //waiting for connection
    std::cout << "Awaiting connection\n";
    acceptor.accept(socket);

    //read operation
    std::cout << "Message recieved\n"; 
    std::string message = _read(socket);
    std::cout << message;

    //write operation
    _send(socket, "Hello from Server!");
    std::cout << "Server sent hello message to client";
}

std::string Network::_read(tcp::socket & socket) {
    boost::asio::streambuf buffer;
    boost::asio::read_until(socket, buffer, "\n");
    std::string data = boost::asio::buffer_cast<const char*>(buffer.data());
    return data;
}

void Network::_send(tcp::socket &socket, const std::string &message) {
    const std::string msg = message + "\n";
    boost::asio::write(socket, boost::asio::buffer(message));
}

void Network::_sendProperResponse(tcp::socket &socket, std::string &recievedMsg) {

}