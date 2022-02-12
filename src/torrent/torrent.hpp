#pragma once

#include "pieces.hpp"
#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace torrent
{
using namespace std;
struct Info
{
    Pieces pieces;
    string fileName;
    uint lengthInBytes;
};

struct File
{
    uint lengthInBytes;
    vector<string> path;
};

class Torrent
{
public:
    explicit Torrent(
        const Info& info,
        const string& announce,
        const optional<vector<string>>& announceList,
        const optional<uint>& creationDate,
        const optional<string>& comment,
        const optional<string>& createdBy);

    explicit Torrent(const string& fileContent);

    string toString() const;

private:
    Info info;
    string announce;
    optional<vector<string>> announceList;
    optional<uint> creationDate;
    optional<string> comment;
    optional<string> createdBy;

    map<string, variant<string, uint>> getInfoMap() const;
};
}
