#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

const std::string SERVER_NAME = "127.0.0.1";
const std::string SERVICE_NAME = "9999";

int main()
{
    boost::asio::io_context context;
    tcp::resolver resolver(context);
    tcp::resolver::results_type endpoints = resolver.resolve(SERVER_NAME, SERVICE_NAME);

    tcp::socket socket(context);
    (void)boost::asio::connect(socket, endpoints);

    for (;;)
    {
        boost::array<char, 128> buf {};
        boost::system::error_code error;
        size_t len = socket.read_some(boost::asio::buffer(buf), error);

        if (error == boost::asio::error::eof)
            break;
        else if (error)
            throw boost::system::system_error(error);

        (void)std::cout.write(buf.data(), static_cast<std::streamsize>(len));
    }

    return 0;
}