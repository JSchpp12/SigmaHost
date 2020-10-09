//
// Created by jacob on 10/8/20.
//

#ifndef SIGMAHOST_MESSAGE_H
#define SIGMAHOST_MESSAGE_H

#include <string>

class Message {
public:
    Message(std::string inMessage); //create a new message object from the string that is passed
    bool IsCommand(); //returns true if the current message is a command
    bool IsRequest(); //returns true if the current message is a request

private:
    struct Type{
        bool isCommand = false;
        bool isRequest = false;
    };
    Type msgType;
    int messageType;
    std::string message, messageCore;

    void _processMessage(); //set the type of the message for easy checking
    bool _isRequest(); //ck if the message is a request from the client
    bool _isCommand(); //check if the message is a command from the client
    std::string _removeBefore(std::string targetString, std::string removeTarget); //removes front part of string before a location
};

#endif //SIGMAHOST_MESSAGE_H
