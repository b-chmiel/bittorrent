#include "bencoding.hpp"
#include <boost/variant.hpp>
#include <cctype>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

using namespace torrent::bencoding;

Bencoding::Bencoding()
    : data(recursive_map())
{
}

Bencoding::Bencoding(uint data)
    : data(data)
{
}

Bencoding::Bencoding(const std::string& data)
    : data(data)
{
}

Bencoding::Bencoding(const std::vector<std::string>& vec)
{
    this->data = recursive_vector();

    for (const auto& el : vec)
    {
        boost::get<recursive_vector>(this->data).push_back(Bencoding(el));
    }
}

Bencoding::Bencoding(const std::vector<Bencoding>& vec)
{
    this->data = recursive_vector();

    for (const auto& el : vec)
    {
        boost::get<recursive_vector>(this->data).push_back(el);
    }
}

void Bencoding::insert(const std::string& key, const Bencoding& value)
{
    if (this->data.type() != typeid(recursive_map))
    {
        throw std::runtime_error("Cannot insert to map");
    }

    boost::get<recursive_map>(this->data)[key] = value;
}

Bencoding Bencoding::operator[](const std::string& key) const
{
    if (this->data.type() == typeid(recursive_map))
    {
        auto map = boost::get<recursive_map>(this->data);
        if (map.contains(key))
        {
            return boost::get<recursive_map>(this->data).at(key).get();
        }

        return Bencoding();
    }

    return Bencoding();
}

Bencoding::operator uint() const
{
    if (this->data.type() == typeid(uint))
    {
        return boost::get<uint>(this->data);
    }

    return 0u;
}

Bencoding::operator std::string() const
{
    if (this->data.type() == typeid(std::string))
    {
        return boost::get<std::string>(this->data);
    }

    return "";
}

Bencoding::operator std::vector<std::string>() const
{
    std::vector<std::string> result {};

    if (this->data.type() == typeid(std::vector<Bencoding>))
    {
        auto vecBenc = boost::get<recursive_vector>(this->data);

        for (const auto& el : vecBenc)
        {
            result.push_back(static_cast<std::string>(el.get()));
        }

        return result;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EncodeVisitor : public boost::static_visitor<std::string>
{
public:
    std::string encode(const std::string& str) const
    {
        return std::to_string(str.length()) + ":" + str;
    }

    std::string encode(uint number) const
    {
        return "i" + std::to_string(number) + "e";
    }

    std::string encode(const Bencoding& var) const
    {
        return boost::apply_visitor(EncodeVisitor(), var.data);
    }

    std::string encode(const recursive_map& dict) const
    {
        std::string result = "d";
        for (const auto& [key, value] : dict)
        {
            result += encode(key);
            result += encode(value.get());
        }
        result += "e";

        return result;
    }

    std::string encode(const recursive_vector& vector) const
    {
        std::string result = "l";
        for (const auto& el : vector)
        {
            result += encode(el.get());
        }
        result += "e";

        return result;
    }

    template <typename T>
    decltype(auto) operator()(T x) const
    {
        return encode(x);
    }
};

std::string Bencoding::toString() const
{
    return boost::apply_visitor(EncodeVisitor(), this->data);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Bencoding decodeString(std::string& str)
{
    std::string charCountDigits = "";
    while (!str.empty() && isdigit(str[0]))
    {
        charCountDigits += str[0];
        str.erase(0, 1);
    }

    int charCount = std::stoi(charCountDigits);

    if (str[0] != ':' || str.empty())
    {
        throw std::runtime_error("Expected ':' before string.");
    }

    str.erase(0, 1);

    std::string result {};
    for (auto i = 0; i < charCount; i++)
    {
        if (str.empty())
        {
            throw std::runtime_error("Incorrect string bencoding.");
        }

        result += str[0];
        str.erase(0, 1);
    }

    return std::move(Bencoding(result));
}

Bencoding decodeInt(std::string& str)
{
    str.erase(0, 1);
    std::string result {};
    while (!str.empty() && str[0] != 'e' && isdigit(str[0]))
    {
        result += str[0];
        str.erase(0, 1);
    }

    if (str[0] != 'e')
    {
        throw std::runtime_error("Expected 'e' after integer.");
    }

    str.erase(0, 1);
    return std::move(Bencoding(stoi(result)));
}

Bencoding decodeItem(std::string& str);

Bencoding decodeList(std::string& str)
{
    str.erase(0, 1);

    std::vector<Bencoding> result {};
    while (!str.empty() && str[0] != 'e')
    {
        result.emplace_back(decodeItem(str));
        str.erase(0, 1);
    }

    if (str[0] != 'e')
    {
        throw std::runtime_error("Expected 'e' after list.");
    }

    str.erase(0, 1);

    return std::move(Bencoding(result));
}

Bencoding decodeDict(std::string& str)
{
    str.erase(0, 1);

    Bencoding result;
    while (!str.empty() && str[0] != 'e')
    {
        auto key = decodeString(str);
        auto value = decodeItem(str);
        result.insert(boost::get<std::string>(key.data), value);
    }

    if (str.empty() || str[0] != 'e')
    {
        throw std::runtime_error("End of dictionary expected.");
    }
    str.erase(0, 1);

    return std::move(result);
}

Bencoding decodeItem(std::string& str)
{
    if (str.empty())
    {
        return Bencoding();
    }

    switch (str[0])
    {
    case 'd':
        return decodeDict(str);
    case 'l':
        return decodeList(str);
    case 'i':
        return decodeInt(str);
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return decodeString(str);
    default:
        throw std::runtime_error("Cannot decode torrent file.");
    }
}

Bencoding Bencoding::decode(const std::string& content)
{
    auto copy = content;
    return decodeItem(copy);
}