#pragma once

#include <map>
#include <string>
#include <variant>
#include <vector>

namespace torrent::bencoding
{
class Bencoding
{
public:
    typedef std::map<
        std::string,
        std::variant<
            std::map<
                std::string,
                std::variant<std::string, uint>>,
            std::vector<std::string>,
            std::string,
            uint>>
        TorrentDict;

    static std::string encode(const TorrentDict&);
    static TorrentDict decode(const std::string&);
};
}