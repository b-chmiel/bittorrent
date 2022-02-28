#pragma once

#include <boost/beast.hpp>
#include <string>

namespace tracker
{
class HttpResponse
{
public:
    std::string toString() const;

    const uint status;
    const std::string body;
};

HttpResponse httpGet(const std::string& url);
}