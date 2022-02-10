#include "tcp_server.hpp"
#include "tcp_connection.hpp"
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

using boost::asio::ip::tcp;

TcpServer::TcpServer(boost::asio::io_context& ctx)
    : context(ctx)
    , acceptor(ctx, tcp::endpoint(tcp::v4(), 9999))
{
    start_accept();
}

void TcpServer::start_accept()
{
    TcpConnection::pointer new_connection = TcpConnection::create(this->context);
    this->acceptor.async_accept(new_connection->get_socket(), boost::bind(&TcpServer::handle_accept, this, new_connection, boost::asio::placeholders::error));
}

void TcpServer::handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error)
{
    if (!error)
    {
        new_connection->start();
    }

    start_accept();
}
