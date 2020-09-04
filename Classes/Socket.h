//
// Created by jacob on 9/4/20.
//
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#ifndef SIGMAHOST_SOCKET_H
#define SIGMAHOST_SOCKET_H


class Socket {

public:

    Socket(){

    }

    bool Initilize();
private:
    int socketNumber = 0;

};


#endif //SIGMAHOST_SOCKET_H
