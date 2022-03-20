#include "client.hpp"
#include "../torrent/torrent.hpp"
#include "../utils/utils.hpp"
#include "handshake.hpp"
#include "request/http_request.hpp"
#include "request/raw_request.hpp"
#include "tracker_request.hpp"
#include "utils/id.hpp"
#include "utils/urlencode.hpp"

using namespace client;

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
        this->getEventName(),
        this->announceUrl);

    try
    {
        const auto response = request.send(request::HttpRequestImpl());
        utils::logging::info("Tracker request response: " + response.toString());
        const Handshake handshake(this->infoHash, this->peerId);
        for (const auto& peer : response.peers)
        {
            utils::logging::info("Sending handshake to: " + peer.toString());
            handshake.send(request::RawRequestImpl(peer.ip, peer.port));
        }
    }
    catch (std::exception& e)
    {
        utils::logging::error(e.what());
        return;
    }
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
    default:
        return "";
    }
}