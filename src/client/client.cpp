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

    const auto initResponse = this->sendInitRequest();
    utils::logging::info("Tracker request response: " + initResponse.toString());
    this->sendHandshake(initResponse);
}

std::string generateHashFromInfo(const torrent::Torrent& torrent)
{
    const auto info = torrent.getInfoMap().toString();
    return utils::sha::sha1(info);
}

TrackerResponse Client::sendInitRequest() const
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
        return request.send(request::HttpRequestImpl());
    }
    catch (std::exception& e)
    {
        throw std::runtime_error("Could not send init request. " + std::string(e.what()));
    }
}

void Client::sendHandshake(const TrackerResponse& response) const
{
        const Handshake handshake(this->infoHash, this->peerId);
        for (const auto& peer : response.peers)
        {
            utils::logging::info("Sending handshake to: " + peer.toString());
            handshake.send(request::RawRequestImpl(peer.ip, peer.port));
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