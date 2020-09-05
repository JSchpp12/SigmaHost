//
// Created by jacob on 9/4/20.
//

#include "Network.h"
#
//create and bind to the socket
bool Network::Initilize() {
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    //setsockopt() //this is optional and allows for more control over socket -- can explore more later
    if (sockFd < 0)
    {
        errorMsg = "Unable to create socket";
        return false;
    }


    return true;
}
