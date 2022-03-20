#pragma once

#include <stdexcept>
#include <string>
#include <vector>

namespace client
{
class Peer
{
public:
    Peer(const std::string& bytes);
    std::string toString() const;

    const std::string url;

private:
    std::vector<std::string> urlSplited;

public:
    const std::string ip;
    const int port;
};
}