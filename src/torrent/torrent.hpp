#pragma once

#include "../utils/utils.hpp"
#include "pieces.hpp"
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace torrent
{
struct Info
{
    Pieces pieces;
    std::string fileName;
    int lengthInBytes;
    friend auto operator<=>(const Info&, const Info&) = default;
};

struct File
{
    int lengthInBytes;
    std::vector<std::string> path;
};

class Torrent
{
public:
    explicit Torrent(
        const Info& info,
        const std::string& announce,
        const std::vector<std::string>& announceList,
        const int creationDate,
        const std::string& comment,
        const std::string& createdBy);

    explicit Torrent(const std::string& fileContent);

    friend auto operator<=>(const Torrent&, const Torrent&) = default;
    std::string toString() const;
    utils::bencoding::Bencoding getInfoMap() const;

    Info info;
    std::string announce;
    std::vector<std::string> announceList;
    int creationDate;
    std::string comment;
    std::string createdBy;
};
}
