//
// Created by jacob on 9/4/20.
//
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#ifndef SIGMAHOST_SOCKET_H
#define SIGMAHOST_SOCKET_H


class Network {

public:

    Network(){
        //constructor

    }
    ~Network() {
        //destructor
        //destroy and unbind socket 
    }

    bool Initilize();
    bool errorState = false;
    std::string errorMsg = "";
private:
    int socketNumber = 0;
    int sockFd; //socket descriptor
    struct sockaddr_in address;
};


#endif //SIGMAHOST_SOCKET_H
