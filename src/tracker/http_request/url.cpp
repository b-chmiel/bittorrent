#include "url.hpp"
#include "../utils/utils.hpp"
#include <stdexcept>
#include <string>

using namespace tracker;

Url::Url(const std::string& url)
{
    auto splitted = utils::str::split(url, ":");
    if (splitted.size() == 2)
    {
        this->scheme = splitted[0];
        auto hostPath = utils::str::split(splitted[1].substr(2), "/");
        this->host = hostPath[0];
        this->path = "/" + hostPath[1];

        if (this->scheme == "http")
        {
            this->port = 80;
        }
        else if (this->scheme == "https")
        {
            this->port = 443;
        }
        else
        {
            throw std::runtime_error("Scheme not implemented: " + this->scheme);
        }
    }
    else if (splitted.size() == 3)
    {
        this->scheme = splitted[0];
        this->host = splitted[1].substr(2);
        auto portPath = utils::str::split(splitted[2], "/");
        this->port = std::stoi(portPath[0]);
        this->path = "/" + portPath[1];
    }
    else
    {
        throw std::runtime_error("Incorrect url format: " + url);
    }
}
