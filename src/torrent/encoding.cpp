#include "encoding.hpp"
#include <set>

using namespace torrent;
using namespace std;

struct Encode
{
    template <typename T>
    decltype(auto) operator()(T x)
    {
        return Encoding::encode(x);
    }
};

string Encoding::encode(const string& str)
{
    return to_string(str.length()) + ":" + str;
}

string Encoding::encode(uint number)
{
    return "i" + to_string(number) + "e";
}

string Encoding::encode(int number)
{
    return "i" + to_string(number) + "e";
}

string Encoding::encode(const vector<string>& vector)
{
    string result = "l";
    for (const auto& el : vector)
    {
        result += Encoding::encode(el);
    }
    result += "e";

    return result;
}

string Encoding::encode(const map<string, variant<string, uint>>& dict)
{
    string result = "d";
    for (const auto& [key, value] : dict)
    {
        result += Encoding::encode(key);
        result += visit(Encode(), value);
    }
    result += "e";

    return result;
}

string Encoding::encode(const Encoding::TorrentDict& dict)
{
    string result = "d";
    for (const auto& [key, value] : dict)
    {
        result += Encoding::encode(key);
        result += visit(Encode(), value);
    }
    result += "e";

    return move(result);
}
