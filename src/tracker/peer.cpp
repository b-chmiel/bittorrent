#include "peer.hpp"

using namespace tracker;

Peer::Peer(const std::string& bytes)
    : url(urlFromBytes(bytes))
{
}

std::string Peer::urlFromBytes(const std::string& bytes) const
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

    const int port = (bytes[4] << 8) | bytes[5];

    return ip + ":" + std::to_string(port);
}

Peer::operator std::string() const
{
    return "{'url': '" + this->url + "'}";
}