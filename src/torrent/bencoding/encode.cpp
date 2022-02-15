// #include "bencoding.hpp"
// #include <set>
// #include <string>
// #include <variant>

// using namespace std;
// using namespace torrent::bencoding;

// string encode(const string& str);
// string encode(uint number);
// string encode(int number);
// string encode(const vector<string>& vector);
// string encode(const map<string, variant<string, uint>>& dict);

// struct Encode
// {
//     template <typename T>
//     decltype(auto) operator()(T x)
//     {
//         return encode(x);
//     }
// };

// string encode(const string& str)
// {
//     return to_string(str.length()) + ":" + str;
// }

// string encode(uint number)
// {
//     return "i" + to_string(number) + "e";
// }

// string encode(int number)
// {
//     return "i" + to_string(number) + "e";
// }

// string encode(const vector<string>& vector)
// {
//     string result = "l";
//     for (const auto& el : vector)
//     {
//         result += encode(el);
//     }
//     result += "e";

//     return result;
// }

// string encode(const map<string, variant<string, uint>>& dict)
// {
//     string result = "d";
//     for (const auto& [key, value] : dict)
//     {
//         result += encode(key);
//         result += visit(Encode(), value);
//     }
//     result += "e";

//     return result;
// }

// string Bencoding::encode(const Bencoding::TorrentDict& dict)
// {
//     string result = "d";
//     for (const auto& [key, value] : dict)
//     {
//         result += encode(key);
//         result += visit(Encode(), value);
//     }
//     result += "e";

//     return move(result);
// }
