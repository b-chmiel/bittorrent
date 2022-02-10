#pragma once

#include "tcp_connection.hpp"
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

using boost::asio::ip::tcp;

class TcpServer
{
public:
    explicit TcpServer(boost::asio::io_context& ctx);

private:
    boost::asio::io_context& context;
    tcp::acceptor acceptor;

    void start_accept();
    void handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error);
};
