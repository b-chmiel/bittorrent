#pragma once

#include <string>

namespace tracker
{
class TrackerRequest
{
public:
    TrackerRequest(
        const std::string& infoHash,
        const std::string& peerId,
        int port,
        int uploadedBytes,
        int downloadedBytes,
        int leftBytes,
        const std::string& event);

    std::string toUrl(const std::string& announceUrl) const;

private:
    const std::string infoHash;
    const std::string peerId;
    const int port;
    const int uploadedBytes;
    const int downloadedBytes;
    const int leftBytes;
    const int compact = 1;
    const std::string event;
};
}
