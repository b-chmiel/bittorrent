#pragma once

#include "../utils/bencoding/bencoding.hpp"
#include "../utils/logging.hpp"
#include "peer.hpp"
#include "request/http_request.hpp"
#include <string>
#include <vector>

namespace tracker
{
class TrackerResponse
{
private:
    const utils::bencoding::Bencoding response;

public:
    TrackerResponse(const request::HttpResponse&);
    std::string toString() const;

    const std::string failureReason;
    const std::string warningMessage;
    const int intervalSecondsBetweenRequests;
    const int minimumInterval;
    const std::string trackerId;
    const int seeders;
    const int leechers;
    const std::vector<Peer> peers;

private:
    static std::vector<Peer> parsePeers(const std::string&);
    static std::string parseString(const utils::bencoding::Bencoding&);
    static int parseInt(const utils::bencoding::Bencoding&);
    static utils::bencoding::Bencoding parseResponse(const request::HttpResponse&);
};
}