#include "bencoding.hpp"
#include <set>
#include <string>
#include <variant>

using namespace std;
using namespace torrent::bencoding;

string innerEncode(const string& str);
string innerEncode(uint number);
string innerEncode(int number);
string innerEncode(const vector<string>& vector);
string innerEncode(const map<string, variant<string, uint>>& dict);

struct Encode
{
    template <typename T>
    decltype(auto) operator()(T x)
    {
        return innerEncode(x);
    }
};

string innerEncode(const string& str)
{
    return to_string(str.length()) + ":" + str;
}

string innerEncode(uint number)
{
    return "i" + to_string(number) + "e";
}

string innerEncode(int number)
{
    return "i" + to_string(number) + "e";
}

string innerEncode(const vector<string>& vector)
{
    string result = "l";
    for (const auto& el : vector)
    {
        result += innerEncode(el);
    }
    result += "e";

    return result;
}

string innerEncode(const map<string, variant<string, uint>>& dict)
{
    string result = "d";
    for (const auto& [key, value] : dict)
    {
        result += innerEncode(key);
        result += visit(Encode(), value);
    }
    result += "e";

    return result;
}

string Bencoding::encode(const Bencoding::TorrentDict& dict)
{
    string result = "d";
    for (const auto& [key, value] : dict)
    {
        result += innerEncode(key);
        result += visit(Encode(), value);
    }
    result += "e";

    return move(result);
}
