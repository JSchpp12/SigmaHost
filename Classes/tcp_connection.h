//
// Created by jacob on 10/21/20.
//

#ifndef SIGMAHOST_TCP_CONNECTION_H
#define SIGMAHOST_TCP_CONNECTION_H

#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "Message.h"

using boost::asio::ip::tcp;

class tcp_connection
        : public boost::enable_shared_from_this<tcp_connection>{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_context& io_context);
    tcp::socket& socket()
    {
        return socket_;
    }

    void start();
private:
    tcp::socket socket_;
    std::string message_;
    boost::asio::streambuf incomingMessage_;
    bool continueConnection_ = true;

    tcp_connection(boost::asio::io_context& io_context)
            : socket_(io_context){};
    void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/); //event handler that is called when a write is complete
    void handle_read(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/); //event handler that is called when a read is complete
};


#endif //SIGMAHOST_TCP_CONNECTION_H
