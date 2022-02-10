#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>

using boost::asio::ip::tcp;

class TcpConnection : public boost::enable_shared_from_this<TcpConnection>
{
public:
    typedef boost::shared_ptr<TcpConnection> pointer;

    explicit TcpConnection(boost::asio::io_context& context);
    static pointer create(boost::asio::io_context& context);
    tcp::socket& get_socket();
    void start();

private:
    std::string message;
    tcp::socket socket;

    static void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
};
