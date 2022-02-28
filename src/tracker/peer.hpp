#pragma once

#include <stdexcept>
#include <string>

namespace tracker
{
class Peer
{
public:
    Peer(const std::string& bytes);
    std::string toString() const;

    const std::string url;

private:
    std::string urlFromBytes(const std::string& bytes) const;
};
}