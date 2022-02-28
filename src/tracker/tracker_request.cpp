#include "tracker_request.hpp"
#include "utils/urlencode.hpp"
#include <sstream>
#include <string>

using namespace tracker;

TrackerRequest::TrackerRequest(
    const std::string& infoHash,
    const std::string& peerId,
    int port,
    int uploadedBytes,
    int downloadedBytes,
    int leftBytes,
    const std::string& event)
    : infoHash(infoHash)
    , peerId(peerId)
    , port(port)
    , uploadedBytes(uploadedBytes)
    , downloadedBytes(downloadedBytes)
    , leftBytes(leftBytes)
    , event(event)
{
}

std::string TrackerRequest::toUrl(const std::string& announceUrl) const
{
    std::stringstream url;
    url << announceUrl;
    url << '?';
    url << "info_hash=" << urlencode::encode(this->infoHash);
    url << '&';
    url << "peer_id=" << urlencode::encode(this->peerId);
    url << '&';
    url << "port=" << this->port;
    url << '&';
    url << "uploaded=" << this->uploadedBytes;
    url << '&';
    url << "downloaded=" << this->downloadedBytes;
    url << '&';
    url << "left=" << this->leftBytes;
    url << '&';
    url << "compact=" << this->compact;
    url << '&';
    url << "event=" << this->event;

    return url.str();
}
