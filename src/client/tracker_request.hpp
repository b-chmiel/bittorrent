#pragma once

#include "../utils/bencoding/bencoding.hpp"
#include "../utils/logging.hpp"
#include "peer.hpp"
#include "request/http_request.hpp"
#include "tracker_response.hpp"
#include <string>
#include <vector>

namespace client
{
class TrackerRequest
{
public:
    TrackerRequest(
        const std::string& infoHash,
        const std::string& peerId,
        int port,
        int uploadedBytes,
        int downloadedBytes,
        int leftBytes,
        const std::string& event,
        const std::string& announceUrl);

    TrackerResponse send(const request::HttpRequest& request) const;

private:
    const std::string infoHash;
    const std::string peerId;
    const int port;
    const int uploadedBytes;
    const int downloadedBytes;
    const int leftBytes;
    const int compact = 1;
    const std::string event;
    const std::string announceUrl;

    std::string toUrl() const;
};
}
