//
// Created by jacob on 9/14/20.
//
#include "Network.h"

void Network::Run() {
    boost::asio::io_service io_service;
    bool continueNetwork = true;
    int errCounter = 0;

    do {
        try {
            //create socket connection
            tcp::socket socket(io_service);

            //listen for new connection
            tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 11000));
            //waiting for connection
            std::cout << "Awaiting connection\n";
            acceptor.accept(socket);
            std::string helloMessage = _read(socket);
            bool continueConnection = _verifyHelloMessage(socket, helloMessage);

            while(continueConnection){
                try{
                    std::cout << "Awaiting Message";
                    //read operation
                    std::string inMessage = _read(socket);
                    if (!erState){
                        std::cout << "Message received" << inMessage << "\n";
                        _processMessage(socket, inMessage);
                    }else{
                        continueConnection = false;
                        std::cout << "Error occurred while reading message from client\n";
                        std::cout << inMessage; //error message will be passed back in the inMessage (might want to change later)
                    }
                }catch (const boost::system::system_error &ex) {
                    std::cout << "An unexpected error has occurred while waiting for client message\n";
                    std::cout << "Additional info: " << ex.what() << "\n";
                    continueConnection = false;
                    continueNetwork = true;
                }
            }
        } catch (const boost::system::system_error &ex) {
            std::cout << "An unknown error has occurred\n";
            std::cout << "Additional info- " << ex.what() << "\n";
            continueNetwork = false;
        }
        errCounter++;
        if (errCounter == 3)
            continueNetwork = false;
    }while(continueNetwork);
}

std::string Network::_read(tcp::socket & socket) {
    std::string data;
    boost::system::error_code ec;
    boost::asio::streambuf buffer;
    boost::asio::read_until(socket, buffer, "<EOF>");
    //if (!ec || ec == boost::asio::error::eof)
    data = boost::asio::buffer_cast<const char*>(buffer.data());
    /*
    else
    {
        erState = true;
        data = "ERROR" + ec.message();
    }
     */
    return data;
}

void Network::_send(tcp::socket& socket, const std::string &message) {
    const std::string msg = message;
    //consider appending "<EOF>" to message
    std::cout << "Writing: " << message << " to client\n";
    boost::asio::write(socket, boost::asio::buffer(msg));
    /*
    bool responseRecieved = false;
    do{


    }while(!responseRecieved);
     */
}

bool Network::_verifyHelloMessage(tcp::socket& socket, std::string inMessage){
    Message* message = new Message(inMessage);
    if (message->IsHello()) {
        _send(socket, "HELLO");
        return true;
    }
    return false;
}

bool Network::_processMessage(tcp::socket& socket, std::string inMessage){
    Message *message = new Message(inMessage);
    if (message->IsValid()){
        if(message->IsHello()){
            std::cout << "Sending hello message to client...\n";
            _send(socket, "HELLO");
            return true;
        }else if(message->IsRequest()){
            if(message->request.isTime)
                _timeRqst();
            return true;
        }else if (message->IsCommand()){
            std::cout << "Command Received \n";
            return true;
        }
    }
    return false;
}

void Network::_timeRqst(){
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    std::string timeMsg = std::to_string(now->tm_year);
}