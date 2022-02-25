#include "bencoding.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <string>
#include <vector>

using namespace utils::bencoding;

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

    return Bencoding(result);
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
    return Bencoding(stoi(result));
}

Bencoding decodeItem(std::string& str);

Bencoding decodeList(std::string& str)
{
    str.erase(0, 1);

    std::vector<Bencoding> result {};
    while (!str.empty() && str[0] != 'e')
    {
        result.emplace_back(decodeItem(str));
    }

    if (str[0] != 'e')
    {
        throw std::runtime_error("Expected 'e' after list.");
    }

    str.erase(0, 1);

    Bencoding r(result);
    return Bencoding(result);
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

    return result;
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
        throw std::runtime_error("Cannot decode bencoded item: " + str);
    }
}

Bencoding Bencoding::decode(const std::string& content)
{
    auto copy = content;
    return decodeItem(copy);
}