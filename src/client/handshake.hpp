#pragma once

#include "../utils/logging.hpp"
#include "../utils/str.hpp"
#include "peer.hpp"
#include "request/raw_request.hpp"
#include "request/url.hpp"
#include <optional>
#include <string>

namespace tracker
{
class HandshakeResponse
{
public:
    explicit HandshakeResponse(const std::string& resp)
        : raw(resp)
    {
        utils::logging::info("Handshake response: " + resp);
    }

    const std::string raw;
};

class Handshake
{
public:
    explicit Handshake(const std::string& infoHash, const std::string& peerId);
    std::string toString() const;
    std::optional<HandshakeResponse> send(const request::RawRequest& request) const;

private:
    const std::string infoHash;
    const std::string peerId;
};
}