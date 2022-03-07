#include "tracker_request.hpp"
#include "../utils/bencoding/bencoding.hpp"
#include "../utils/logging.hpp"
#include "peer.hpp"
#include "request/http_request.hpp"
#include "utils/urlencode.hpp"
#include <sstream>
#include <string>
#include <vector>

using namespace utils::bencoding;
using namespace tracker;

TrackerRequest::TrackerRequest(
    const std::string& _infoHash,
    const std::string& _peerId,
    int _port,
    int _uploadedBytes,
    int _downloadedBytes,
    int _leftBytes,
    const std::string& _event,
    const std::string& _announceUrl)
    : infoHash(_infoHash)
    , peerId(_peerId)
    , port(_port)
    , uploadedBytes(_uploadedBytes)
    , downloadedBytes(_downloadedBytes)
    , leftBytes(_leftBytes)
    , event(_event)
    , announceUrl(_announceUrl)
{
}

TrackerResponse TrackerRequest::send(const request::HttpRequest& request) const
{
    utils::logging::info(this->toUrl());
    return TrackerResponse(request.get(this->toUrl()));
}

std::string TrackerRequest::toUrl() const
{
    std::stringstream url;
    url << this->announceUrl;
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
