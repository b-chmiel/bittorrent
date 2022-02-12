#pragma once

#include <map>
#include <set>
#include <string>
#include <variant>
#include <vector>

namespace torrent
{
using namespace std;

class Encoding
{
public:
    typedef map<string, variant<map<string, variant<string, uint>>, vector<string>, string, uint>> TorrentDict;

    static string encode(const string&);
    static string encode(uint);
    static string encode(int);
    static string encode(const vector<string>&);
    static string encode(const map<string, variant<string, uint>>&);

    static string encode(const TorrentDict&);
};
}
