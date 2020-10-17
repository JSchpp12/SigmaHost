//
// Created by jacob on 10/8/20.
//

#ifndef SIGMAHOST_MESSAGE_H
#define SIGMAHOST_MESSAGE_H

#include <string>

class Message {
public:
    struct Request{
        bool isTime = false;
    };
    Request request;
    Message(std::string inMessage); //create a new message object from the string that is passed
    bool IsCommand(); //returns true if the current message is a command
    bool IsRequest(); //returns true if the current message is a request
    bool IsValid(); //returns true if the current message is valid
    bool IsHello(); //returns true if the current message is a handshake
private:
    struct Type{
        bool isCommand = false;
        bool isRequest = false;
        bool isValid = false;
        bool isHello = false;
    };
    Type msgType;
    std::string message, messageCore;

    void _processMessage(); //set the type of the message for easy checking
    void _processRequest(); //process the request sent in the message
    void _processCommand(); //process the command sent in the message
    std::string _removeBefore(std::string targetString, std::string removeTarget); //removes front part of string before a location
    bool _contains(std::string* targetString, std::string testString); //returns true if the target string contains the testString
};

#endif //SIGMAHOST_MESSAGE_H
