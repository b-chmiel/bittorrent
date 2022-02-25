#pragma once

#include <boost/beast.hpp>
#include <string>

namespace tracker
{
class HttpResponse
{
public:
    explicit operator std::string() const;

    const uint status;
    const std::string body;
};

HttpResponse httpGet(const std::string& url);
}