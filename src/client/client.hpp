#pragma once

#include "../torrent/torrent.hpp"
#include <string>
#include <vector>

namespace client
{
enum class Event
{
    STARTED,
    STOPPED,
    COMPLETED
};

class Client
{
public:
    Client() = delete;
    Client(const torrent::Torrent&);

private:
    const std::string infoHash;
    const std::string peerId;
    const std::string announceUrl;
    int uploadedBytes;
    int downloadedBytes;
    int leftBytes;

    const int port = 6767;
    const int numWantPeers = 50;
    Event event = Event::STARTED;

    void initRequest();
    std::string getEventName() const;
};
}