#include "response.hpp"
#include "../utils/bencoding/bencoding.hpp"
#include "../utils/logging.hpp"
#include "http_request/http_request.hpp"
#include "peer.hpp"
#include <string>
#include <vector>

using namespace tracker;
using namespace utils::bencoding;

Bencoding parseResponse(const HttpResponse& response);
std::string parseString(const Bencoding&);
int parseInt(const Bencoding&);
std::vector<Peer> parsePeers(const Bencoding&);

TrackerResponse::TrackerResponse(const HttpResponse& r)
    : response(parseResponse(r))
    , failureReason(parseString(response["failure reason"]))
    , warningMessage(parseString(response["warning message"]))
    , intervalSecondsBetweenRequests(parseInt(response["interval"]))
    , minimumInterval(parseInt(response["min interval"]))
    , trackerId(parseString(response["tracker id"]))
    , seeders(parseInt(response["complete"]))
    , leechers(parseInt(response["incomplete"]))
    , peers(parsePeers(response["peers"]))
{
}

Bencoding parseResponse(const HttpResponse& response)
{
    try
    {
        return Bencoding::decode(response.body);
    }
    catch (const std::exception& e)
    {
        utils::logging::error("Cannot parse tracker response: " + static_cast<std::string>(response));
        return Bencoding();
    }
}

std::string parseString(const Bencoding& b)
{
    return static_cast<std::string>(b);
}

int parseInt(const Bencoding& b)
{
    return static_cast<int>(b);
}

std::vector<Peer> parsePeers(const Bencoding& peers)
{
    std::string peersStr = parseString(peers);

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

TrackerResponse::operator std::string() const
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
        ss << static_cast<std::string>(peer) << ", ";
    }
    ss << "]}";

    return ss.str();
}
