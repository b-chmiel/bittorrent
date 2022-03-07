#include "http_request.hpp"
#include "../utils/utils.hpp"
#include "url.hpp"
#include <algorithm>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

using boost::asio::ip::tcp;
namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;

using namespace tracker::request;

class BeastRequest
{
public:
    BeastRequest(const std::string& _host, const int _port)
        : context()
        , resolver(context)
        , stream(context)
        , host(_host)
        , port(std::to_string(_port))
    {
        const auto lookup = resolver.resolve(this->host, this->port);
        stream.connect(lookup);
    }

    HttpResponse get(const std::string& url)
    {
        const auto request = prepareRequest(url);

        http::write(stream, request);
        utils::logging::info("Sending request: GET " + this->host + ':' + this->port + url);

        beast::flat_buffer buffer;
        http::response<http::string_body> response;
        http::read(stream, buffer, response);

        return HttpResponse { .status = response.result_int(), .body = response.body() };
    }

    ~BeastRequest()
    {
        beast::error_code ec;
        this->stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        if (ec && ec != beast::errc::not_connected)
        {
            throw beast::system_error { ec };
        }
    }

private:
    asio::io_context context;
    tcp::resolver resolver;
    beast::tcp_stream stream;
    std::string host;
    std::string port;
    const int httpVersion = 11;

    beast::http::request<beast::http::string_body> prepareRequest(const std::string& url) const
    {
        http::request<http::string_body> req { http::verb::get, url, this->httpVersion };
        req.set(http::field::host, this->host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        return req;
    }
};

std::string HttpResponse::toString() const
{
    std::stringstream ss;
    ss << "{'status': " << this->status << ", "
       << "'body': '" << this->body << "'}";
    return ss.str();
}

// FIXME optimize url parsing
HttpResponse HttpRequestImpl::get(const std::string& url) const
{
    Url parsed(url);
    BeastRequest r(parsed.host, parsed.port);
    return r.get(parsed.path);
}