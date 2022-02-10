#include "tcp_server.hpp"
#include "tcp_connection.hpp"
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

using boost::asio::ip::tcp;

TcpServer::TcpServer(boost::asio::io_context& ctx)
    : context(ctx)
    , acceptor(ctx, tcp::endpoint(tcp::v4(), 9999))
{
    startAccept();
}

void TcpServer::startAccept()
{
    TcpConnection::pointer newConnection = TcpConnection::create(this->context);
    this->acceptor.async_accept(newConnection->getSocket(), boost::bind(&TcpServer::handleAccept, this, newConnection, boost::asio::placeholders::error));
}

void TcpServer::handleAccept(TcpConnection::pointer new_connection, const boost::system::error_code& error)
{
    if (!error)
    {
        new_connection->start();
    }

    startAccept();
}
