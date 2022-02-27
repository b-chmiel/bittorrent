#include "client.hpp"
#include "../torrent/torrent.hpp"
#include "../utils/utils.hpp"
#include "http_request/http_request.hpp"
#include "tracker_request.hpp"
#include "tracker_response.hpp"
#include "utils/id.hpp"
#include "utils/urlencode.hpp"
#include <sstream>

using namespace tracker;

std::string generateHashFromInfo(const torrent::Torrent& torrent);

Client::Client(const torrent::Torrent& torrent)
    : infoHash(generateHashFromInfo(torrent))
    , peerId(id::generate())
    , announceUrl(torrent.announce)
{
    this->uploadedBytes = 0;
    this->downloadedBytes = 0;
    this->leftBytes = torrent.info.lengthInBytes;
    initRequest();
}

std::string generateHashFromInfo(const torrent::Torrent& torrent)
{
    auto info = torrent.getInfoMap().toString();
    return utils::sha::sha1(info);
}

void Client::initRequest()
{
    TrackerRequest request(
        this->infoHash,
        this->peerId,
        this->port,
        this->uploadedBytes,
        this->downloadedBytes,
        this->leftBytes,
        this->getEventName());

    auto httpResponse = tracker::httpGet(request.toUrl(this->announceUrl));
    TrackerResponse response(httpResponse);

    utils::logging::info(static_cast<std::string>(httpResponse));
    utils::logging::info(static_cast<std::string>(response));
}

std::string Client::getEventName() const
{
    switch (this->event)
    {
    case Event::COMPLETED:
        return "completed";
    case Event::STARTED:
        return "started";
    case Event::STOPPED:
        return "stopped";
    }
}