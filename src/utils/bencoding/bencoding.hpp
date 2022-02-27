#pragma once

#include <boost/variant/recursive_wrapper.hpp>
#include <boost/variant/variant.hpp>
#include <map>
#include <string>
#include <vector>

namespace utils::bencoding
{
class Bencoding;

using recursive_vector = std::vector<boost::recursive_wrapper<Bencoding>>;
using recursive_map = std::map<std::string, boost::recursive_wrapper<Bencoding>>;

typedef boost::variant<
    recursive_map,
    recursive_vector,
    std::string,
    int>
    BencodingData;

class Bencoding
{
public:
    Bencoding();
    Bencoding(int);
    Bencoding(const std::string&);
    Bencoding(const std::vector<std::string>&);
    Bencoding(const std::vector<Bencoding>& vec);

    std::string toString() const;
    void insert(const std::string& key, const Bencoding&);

    explicit operator int() const;
    explicit operator std::string() const;
    explicit operator std::vector<std::string>() const;

    Bencoding operator[](const std::string& key) const;

    static Bencoding decode(const std::string&);

    BencodingData data;
};
}