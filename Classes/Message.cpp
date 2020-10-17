//
// Message class to handle incoming messages from client
//

#include <iostream>
#include "Message.h"

Message::Message(std::string inMessage) {
    message = inMessage;
    _processMessage();
}

bool Message::IsCommand() {return msgType.isCommand;}
bool Message::IsRequest() {return msgType.isRequest;}
bool Message::IsValid()   {return msgType.isValid;}
bool Message::IsHello() {return msgType.isHello;}
void Message::_processMessage() {
    if (_contains(&message, "HELLO")){
        msgType.isHello = true;
        msgType.isValid = true;
    } else if(_contains(&message, "REQUEST")) {
        messageCore = _removeBefore(message, "REQUEST:");
        msgType.isRequest = true;
        msgType.isValid = true;
        _processRequest();
    }else if(_contains(&message, "COMMAND")) {
        messageCore = _removeBefore(message,"COMMAND:");
        msgType.isCommand = true;
        msgType.isValid = true;
    }else {
        std::cout << "Unknown Message type received";
        msgType.isValid = false;
    }
}

void Message::_processRequest() {
    if(_contains(&messageCore, "time")) {
        request.isTime = true;
    }else{
        msgType.isValid = false;
    }
}

std::string Message::_removeBefore(std::string targetString, std::string removeTarget) {
    std::size_t found = targetString.find(removeTarget);
    if (found != std::string::npos){
        targetString.erase(found, found+removeTarget.size());
    }
    return targetString;
}

bool Message::_contains(std::string* targetString, std::string testString) {
    std::size_t found = targetString->find(testString);
    if (found != std::string::npos)
        return true;
    else
        return false;
}