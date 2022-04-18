#pragma once

#include <boost/beast.hpp>
#include <string>

namespace client::request
{
struct HttpResponse
{
    std::string toString() const;

    const uint status;
    const std::string body;
};

struct HttpRequest
{
    virtual HttpResponse get(const std::string& url) const = 0;
    virtual ~HttpRequest() = default;
};

class HttpRequestImpl final : public HttpRequest
{
public:
    HttpResponse get(const std::string& url) const override;
};
}