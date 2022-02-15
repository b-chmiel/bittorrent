#include "torrent.hpp"
#include "bencoding/bencoding.hpp"
#include <boost/variant.hpp>
#include <iostream>
#include <map>
#include <string>

using namespace std;
using namespace torrent;

Torrent::Torrent(const Info& info, const string& announce, const vector<string>& announceList, const uint& creationDate, const string& comment, const string& createdBy)
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
    auto bencoded = bencoding::Bencoding::decode(content);
    auto pieces = Pieces(static_cast<std::string>(bencoded["info"]["pieces"]));
    pieces.pieceLengthInBytes = static_cast<uint>(bencoded["info"]["piece length"]);

    auto fileName = static_cast<std::string>(bencoded["info"]["name"]);
    auto lengthInBytes = static_cast<uint>(bencoded["info"]["length"]);
    auto announce = static_cast<std::string>(bencoded["announce"]);
    auto announceList = static_cast<std::vector<std::string>>(bencoded["announce-list"]);
    auto creationDate = static_cast<uint>(bencoded["creation date"]);
    auto comment = static_cast<std::string>(bencoded["comment"]);
    auto createdBy = static_cast<std::string>(bencoded["created by"]);

    this->info = Info { .pieces = pieces, .fileName = fileName, .lengthInBytes = lengthInBytes };
    this->announce = announce;
    this->announceList = announceList;
    this->creationDate = creationDate;
    this->comment = comment;
    this->createdBy = createdBy;
}

bencoding::Bencoding Torrent::getInfoMap() const
{
    bencoding::Bencoding result;
    result.insert("length", this->info.lengthInBytes);
    result.insert("name", this->info.fileName);
    result.insert("piece length", this->info.pieces.pieceLengthInBytes);
    result.insert("pieces", this->info.pieces.toString());

    return move(result);
}

string Torrent::toString() const
{
    bencoding::Bencoding dict;
    dict.insert("info", getInfoMap());
    dict.insert("announce", this->announce);

    if (this->createdBy != "")
    {
        dict.insert("created by", this->createdBy);
    }

    if (this->creationDate != 0u)
    {
        dict.insert("creation date", this->creationDate);
    }

    if (this->comment != "")
    {
        dict.insert("comment", this->comment);
    }

    if (this->announceList.size() != 0)
    {
        dict.insert("announce-list", bencoding::Bencoding(this->announceList));
    }

    return move(dict.toString());
}
