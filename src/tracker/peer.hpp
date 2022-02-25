#pragma once

#include <stdexcept>
#include <string>

namespace tracker
{
class Peer
{
public:
    Peer(const std::string& bytes);
    explicit operator std::string() const;

    const std::string url;

private:
    std::string urlFromBytes(const std::string& bytes) const;
};
}