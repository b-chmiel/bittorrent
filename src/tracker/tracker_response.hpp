#pragma once

#include "../utils/bencoding/bencoding.hpp"
#include "http_request/http_request.hpp"
#include "peer.hpp"
#include <string>
#include <vector>

namespace tracker
{
class TrackerResponse
{
private:
    const utils::bencoding::Bencoding response;

public:
    TrackerResponse(const HttpResponse&);
    explicit operator std::string() const;

    const std::string failureReason;
    const std::string warningMessage;
    const int intervalSecondsBetweenRequests;
    const int minimumInterval;
    const std::string trackerId;
    const int seeders;
    const int leechers;
    const std::vector<Peer> peers;
};
}