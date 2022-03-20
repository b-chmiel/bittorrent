#include "handshake.hpp"
#include "../utils/logging.hpp"
#include "peer.hpp"
#include <array>
#include <optional>
#include <string>

using namespace client;

Handshake::Handshake(const std::string& _infoHash, const std::string& _peerId)
    : infoHash(_infoHash)
    , peerId(_peerId)
{
}

std::string Handshake::toString() const
{
    const char pstrlen = 19;
    const std::string pstr = "BitTorrent protocol";
    const uint64_t reserved = 0;
    constexpr int size = 1 + pstrlen + sizeof(reserved) / sizeof(char) + 20 + 20;

    std::array<char, size> result {};

    size_t index = 0;
    result[index++] = pstrlen;

    for (const auto ch : pstr)
    {
        result[index++] = ch;
    }

    for (size_t i = 0; i < sizeof(reserved); i += sizeof(char))
    {
        result[index++] = 0;
    }

    for (const auto ch : infoHash)
    {
        result[index++] = ch;
    }

    for (const auto ch : peerId)
    {
        result[index++] = ch;
    }

    return std::string(result.begin(), result.end());
}

std::optional<HandshakeResponse> Handshake::send(const request::RawRequest& request) const
{
    const auto response = request.send(this->toString());

    return response ? std::optional(HandshakeResponse(response.value())) : std::nullopt;
}