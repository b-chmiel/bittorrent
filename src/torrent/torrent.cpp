#include "torrent.hpp"
#include "encoding.hpp"
#include <iostream>
#include <map>
#include <optional>
#include <string>

using namespace std;
using namespace torrent;

Torrent::Torrent(const Info& info, const string& announce, const optional<vector<string>>& announceList, const optional<uint>& creationDate, const optional<string>& comment, const optional<string>& createdBy)
    : info(info)
    , announce(announce)
    , announceList(announceList)
    , creationDate(creationDate)
    , comment(comment)
    , createdBy(createdBy)
{
}

Torrent::Torrent(const string& content)
{
    this->info = Info { .pieces = Pieces("", 0), .fileName = "", .lengthInBytes = 0 };
    this->announce = "";
    this->announceList = nullopt;
    this->creationDate = nullopt;
    this->comment = nullopt;
    this->createdBy = nullopt;
}

string Torrent::toString() const
{
    Encoding::TorrentDict result = {
        { "info", getInfoMap() },
        { "announce", this->announce },
    };

    if (this->createdBy.has_value())
    {
        result["created by"] = this->createdBy.value();
    }

    if (this->creationDate.has_value())
    {
        result["creation date"] = this->creationDate.value();
    }

    if (this->comment.has_value())
    {
        result["comment"] = this->comment.value();
    }

    if (this->announceList.has_value())
    {
        result["announce-list"] = this->announceList.value();
    }

    return move(Encoding::encode(result));
}

map<string, variant<string, uint>> Torrent::getInfoMap() const
{
    return {
        { "length", this->info.lengthInBytes },
        { "name", this->info.fileName },
        { "piece length", this->info.pieces.pieceLengthInBytes },
        { "pieces", this->info.pieces.toString() }
    };
}
