#include "tracker_response.hpp"
#include "../utils/bencoding/bencoding.hpp"
#include "../utils/logging.hpp"
#include "peer.hpp"
#include <string>
#include <vector>

using namespace client;
using namespace utils::bencoding;

TrackerResponse::TrackerResponse(const request::HttpResponse& r)
    : response(parseResponse(r))
    , failureReason(parseString(response["failure reason"]))
    , warningMessage(parseString(response["warning message"]))
    , intervalSecondsBetweenRequests(parseInt(response["interval"]))
    , minimumInterval(parseInt(response["min interval"]))
    , trackerId(parseString(response["tracker id"]))
    , seeders(parseInt(response["complete"]))
    , leechers(parseInt(response["incomplete"]))
    , peers(parsePeers(parseString(response["peers"])))

{
}

std::string TrackerResponse::toString() const
{
    std::stringstream ss;
    ss << "{'failure reason': '" << this->failureReason << "', ";
    ss << "'warning message': '" << this->warningMessage << "', ";
    ss << "'interval': " << this->intervalSecondsBetweenRequests << ", ";
    ss << "'min interval': " << this->minimumInterval << ", ";
    ss << "'tracker id': '" << this->trackerId << "', ";
    ss << "'seeders': " << this->seeders << ", ";
    ss << "'leechers': " << this->leechers << ", ";
    ss << "'peers': [";
    for (const auto& peer : this->peers)
    {
        ss << peer.toString() << ", ";
    }
    ss << "]}";

    return ss.str();
}

std::vector<Peer> TrackerResponse::parsePeers(const std::string& peersStr)
{
    if (peersStr.length() % 6 != 0)
    {
        utils::logging::error("Cannot parse peers.");
        return {};
    }

    std::vector<Peer> result {};
    std::string peer {};
    for (size_t i = 0; i < peersStr.size(); ++i)
    {
        if (i % 6 == 0 && i != 0)
        {
            result.emplace_back(peer);
            peer = "";
        }
        peer += peersStr[i];
    }

    return result;
}

std::string TrackerResponse::parseString(const Bencoding& b)
{
    return static_cast<std::string>(b);
}

int TrackerResponse::parseInt(const Bencoding& b)
{
    return static_cast<int>(b);
}

Bencoding TrackerResponse::parseResponse(const request::HttpResponse& resp)
{
    try
    {
        return Bencoding::decode(resp.body);
    }
    catch (const std::exception& e)
    {
        utils::logging::error("Cannot parse tracker response: " + resp.toString());
        return Bencoding();
    }
}