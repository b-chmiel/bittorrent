#pragma once

#include <boost/variant.hpp>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace torrent::bencoding
{
class Bencoding;

using recursive_vector = std::vector<boost::recursive_wrapper<Bencoding>>;
using recursive_map = std::map<std::string, boost::recursive_wrapper<Bencoding>>;

typedef boost::variant<
    recursive_map,
    recursive_vector,
    std::string,
    uint>
    BencodingData;

class Bencoding
{
public:
    Bencoding();
    Bencoding(uint);
    Bencoding(const std::string&);
    Bencoding(const std::vector<std::string>&);
    Bencoding(const std::vector<Bencoding>& vec);

    std::string toString() const;
    void insert(const std::string& key, const Bencoding&);

    explicit operator uint() const;
    explicit operator std::string() const;
    explicit operator std::vector<std::string>() const;

    Bencoding operator[](const std::string& key) const;

    static Bencoding decode(const std::string&);

    BencodingData data;
};
}