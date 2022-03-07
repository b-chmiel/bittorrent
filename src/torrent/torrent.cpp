#include "torrent.hpp"
#include "../utils/bencoding/bencoding.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace torrent;

Torrent::Torrent(
    const Info& _info,
    const string& _announce,
    const vector<string>& _announceList,
    const int _creationDate,
    const string& _comment,
    const string& _createdBy)
    : info(_info)
    , announce(_announce)
    , announceList(_announceList)
    , creationDate(_creationDate)
    , comment(_comment)
    , createdBy(_createdBy)
{
}

Torrent::Torrent(const string& content)
{
    const auto bencoded = utils::bencoding::Bencoding::decode(content);
    auto pieces = Pieces(static_cast<std::string>(bencoded["info"]["pieces"]));
    pieces.pieceLengthInBytes = static_cast<int>(bencoded["info"]["piece length"]);

    const auto fileName = static_cast<std::string>(bencoded["info"]["name"]);
    const auto lengthInBytes = static_cast<int>(bencoded["info"]["length"]);
    const auto _announce = static_cast<std::string>(bencoded["announce"]);
    const auto _announceList = static_cast<std::vector<std::string>>(bencoded["announce-list"]);
    const auto _creationDate = static_cast<int>(bencoded["creation date"]);
    const auto _comment = static_cast<std::string>(bencoded["comment"]);
    const auto _createdBy = static_cast<std::string>(bencoded["created by"]);

    this->info = Info { .pieces = pieces, .fileName = fileName, .lengthInBytes = lengthInBytes };
    this->announce = _announce;
    this->announceList = _announceList;
    this->creationDate = _creationDate;
    this->comment = _comment;
    this->createdBy = _createdBy;
}

utils::bencoding::Bencoding Torrent::getInfoMap() const
{
    utils::bencoding::Bencoding result;
    result.insert("length", this->info.lengthInBytes);
    result.insert("name", this->info.fileName);
    result.insert("piece length", this->info.pieces.pieceLengthInBytes);
    result.insert("pieces", this->info.pieces.toString());

    return result;
}

string Torrent::toString() const
{
    utils::bencoding::Bencoding dict;
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
        dict.insert("announce-list", utils::bencoding::Bencoding(this->announceList));
    }

    return dict.toString();
}
