#include "raw_request.hpp"
#include "../../utils/logging.hpp"
#include <boost/asio.hpp>
#include <optional>
#include <sstream>
#include <string>

using namespace tracker::request;

using boost::asio::ip::tcp;
namespace asio = boost::asio;

RawRequestImpl::RawRequestImpl(const std::string& _url, int _port)
    : url(_url)
    , port(_port)
{
}

std::optional<std::string> RawRequestImpl::send(const std::string& message) const
{
    asio::io_service service;
    tcp::socket socket(service);

    const tcp::endpoint endpoint(asio::ip::address::from_string(this->url), static_cast<unsigned short>(this->port));

    try
    {
        socket.connect(endpoint);
    }
    catch (std::exception& e)
    {
        std::stringstream ss;
        ss << "Cannot send raw request to: ";
        ss << this->url;
        ss << ':';
        ss << this->port;
        ss << ". ";
        ss << e.what();

        utils::logging::warn(ss.str());

        return std::nullopt;
    }

    boost::system::error_code error;
    asio::write(socket, asio::buffer(message), error);
    if (error)
    {
        utils::logging::error("Send failed: " + error.message());
    }
    else
    {
        asio::streambuf receive;
        std::stringstream ss;
        while (asio::read(socket, receive, asio::transfer_at_least(68), error))
        {
            ss << &receive;
            break;
        }
        if (error && error != asio::error::eof)
        {
            utils::logging::error("Receive failed: " + error.message());
        }

        return { ss.str() };
    }

    return std::nullopt;
}