//
// Created by jacob on 10/21/20.
//

#include <iomanip>
#include "tcp_connection.h"

tcp_connection::pointer tcp_connection::create(boost::asio::io_context &io_context) {
    return pointer(new tcp_connection(io_context));
}

void tcp_connection::start() {
    bool continueReading = false;

    boost::asio::async_read_until(socket_, incomingMessage_, "<EOF>",
                                  boost::bind(&tcp_connection::handle_read, shared_from_this(),
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));

    /*
    boost::asio::async_write(socket_, boost::asio::buffer(message_),
                             boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
                                         */
}

void tcp_connection::handle_write(const boost::system::error_code &, size_t) {
    std::cout << "Message sent to client\n";
}

void tcp_connection::handle_read(const boost::system::error_code &readErr, size_t numBytes){
    std::string data = boost::asio::buffer_cast<const char*>(incomingMessage_.data());
    std::cout << "Message received from client:" << data << "\n";
    Message *message = new Message(data);

    if (message->IsCommand()){
        std::cout << "Command received from client!\n";
    }else if (message->IsRequest()){
        std::cout << "Request received from client!\n";
        if (message->request.isTime){
            std::cout << "Client is requesting time, processing...\n";
            std::string serverTime = generateSystemTime();
            sendMessage(serverTime);
        }
    }else if (message->IsHello()){
        completedHandshake = true;
        std::cout << "Handhshake verified...\n";
        sendMessage("HELLO<EOF>");
    }
}

void tcp_connection::sendMessage(std::string outboundMessage){
    std::cout << "Sending message to client " + outboundMessage + "\n";
    boost::asio::async_write(socket_, boost::asio::buffer(outboundMessage),
                             boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

std::string tcp_connection::generateSystemTime(){
    std::string month, day, year, hour, minute, second, millisecond;
    std::stringstream strstream, monthStream, minuteStream, secondStream;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    //get nano and milliseconds
    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    strstream << start_time.tv_usec;
    strstream >> millisecond;

    //get larger date information
    month = padString(2, ltm->tm_mon+1);
    day = padString(2, ltm->tm_mday);
    year = std::to_string(1900 + ltm->tm_year);
    hour = padString(2, ltm->tm_hour);
    minute = padString(2, ltm->tm_min);
    second = padString(2, ltm->tm_sec);

    std::string formedTime = month + "/" + day + "/" + year + " " + hour + ":" + minute + ":" + second + "." + millisecond;
    return formedTime;
}

std::string tcp_connection::padString(int pad, int input) {
    std::stringstream stream;
    std::string returnString;
    stream << std::setfill('0') << std::setw(pad) << std::to_string(input);
    stream >> returnString;
    return returnString;
}