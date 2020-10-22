//
// Created by jacob on 10/21/20.
//

#include "tcp_connection.h"

tcp_connection::pointer tcp_connection::create(boost::asio::io_context &io_context) {
    return pointer(new tcp_connection(io_context));
}

void tcp_connection::start() {
    message_ = "BABY MESSAGE\n";

    boost::asio::async_write(socket_, boost::asio::buffer(message_),
                             boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void tcp_connection::handle_write(const boost::system::error_code &, size_t) {
    std::cout << "Message sent to client";
}

