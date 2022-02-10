#include "server/tcp_server.hpp"
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main()
{
    try
    {
        std::cout << "SERVER START" << std::endl;

        boost::asio::io_context context;
        TcpServer server(context);
        context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
