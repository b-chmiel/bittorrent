#pragma once

#include <string>

namespace client
{
class Url
{
public:
    std::string scheme;
    std::string host;
    std::string path;
    int port;

    Url(const std::string& url);
};
}