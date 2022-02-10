#include "tcp_connection.hpp"
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>

using boost::asio::ip::tcp;

std::string daytimeString();

TcpConnection::TcpConnection(boost::asio::io_context& context)
    : socket(context)
{
}

TcpConnection::pointer TcpConnection::create(boost::asio::io_context& context)
{
    return TcpConnection::pointer(new TcpConnection(context));
}

tcp::socket& TcpConnection::getSocket()
{
    return this->socket;
}

void TcpConnection::start()
{
    this->message = daytimeString();
    boost::asio::async_write(
        this->socket,
        boost::asio::buffer(this->message),
        boost::bind(&TcpConnection::handleWrite,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

std::string daytimeString()
{
    std::cout << "WAITING" << std::endl;

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);

    auto now = std::time(nullptr);
    return std::ctime(&now);
}

void TcpConnection::handleWrite(const boost::system::error_code& error, size_t bytesTransferred)
{
    std::cout << "SENT" << std::endl;
}
