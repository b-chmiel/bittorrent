#include "peer.hpp"
#include "../utils/str.hpp"
#include <bit>

using namespace client;

std::string urlFromBytes(const std::string& bytes);

Peer::Peer(const std::string& bytes)
    : url(urlFromBytes(bytes))
    , urlSplited(utils::str::split(url, ":"))
    , ip(urlSplited[0])
    , port(std::stoi(urlSplited[1]))
{
}

std::string urlFromBytes(const std::string& bytes)
{
    const int urlSize = 6;
    if (bytes.length() != urlSize)
    {
        throw std::runtime_error("Cannot parse peer info from bytes.");
    }

    std::string ip {};

    for (size_t i = 0; i < 4; i++)
    {
        ip += std::to_string(static_cast<int>(bytes[i]));
        if (i != 3)
        {
            ip += '.';
        }
    }

    const uint16_t port = static_cast<uint16_t>((static_cast<uint8_t>(bytes[5])) | (static_cast<uint8_t>(bytes[4]) << 8));

    return ip + ":" + std::to_string(port);
}

std::string Peer::toString() const
{
    return "{'url': '" + this->url + "'}";
}