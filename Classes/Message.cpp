//
// Message class to handle incoming messages from client
//

#include <iostream>
#include "Message.h"

Message::Message(std::string inMessage){
    message = inMessage;
    _processMessage();
}

bool Message::IsCommand() {return msgType.isCommand;}
bool Message::IsRequest() {return msgType.isRequest;}

void Message::_processMessage() {

    if(_isRequest()){
        _removeBefore(message, "REQUEST");
    }else if (_isCommand()){

    }else{
        std::cout << "Unknown Message type received";
    }
}

bool Message::_isRequest(){
    std::size_t found = message.find("REQUEST");
    //check if the message is a request
    if (found != std::string::npos){
        msgType.isRequest = true;
        return true;
    }else{
        return false;
    }
}

bool Message::_isCommand(){

}

std::string Message::_removeBefore(std::string targetString, std::string removeTarget){
    std::size_t found = targetString.find(removeTarget);
    if (found != std::string::npos){
        targetString.erase(found, found+removeTarget.size());
    }
    return targetString;
}