//
// Created by jacob on 10/21/20.
//

#ifndef SIGMAHOST_TCP_SERVER_H
#define SIGMAHOST_TCP_SERVER_H

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "tcp_connection.h"

using boost::asio::ip::tcp;

class tcp_server {
public:
    tcp_server(boost::asio::io_context& io_context)
            : io_context_(io_context),
              acceptor_(io_context, tcp::endpoint(tcp::v4(), 10005)){
        std::cout << "Awaiting Connection\n";
        start_accept();
    };

private:
    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;


    typedef boost::shared_ptr<tcp_connection> pointer;
    void start_accept();
    void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error);
};


#endif //SIGMAHOST_TCP_SERVER_H
