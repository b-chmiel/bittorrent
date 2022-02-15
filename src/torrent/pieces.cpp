#include "pieces.hpp"
#include <boost/uuid/detail/sha1.hpp>
#include <cmath>
#include <string>

using namespace std;
using namespace torrent;

string sha1(const string& str)
{
    // https://stackoverflow.com/questions/28489153/how-to-portably-compute-a-sha1-hash-in-c
    boost::uuids::detail::sha1 sha1;
    sha1.process_bytes(str.data(), str.size());
    unsigned hash[5] = { 0 };
    sha1.get_digest(hash);

    string result = "";
    for (const auto ch : hash)
    {
        for (int j = sizeof(hash[0]) - 1; j >= 0; j--)
        {
            result += (char)((ch & (255 << j * 8)) >> j * 8);
        }
    }

    return move(result);
}

Pieces::Pieces(const std::string& concatenatedHashes)
    : concatenatedHashes(concatenatedHashes)
{
}

Pieces::Pieces(string fileContents, uint pieceLengthInBytes)
{
    auto i = 0;
    string result = "";
    string piece;
    for (int i = 0; i < fileContents.size(); i += pieceLengthInBytes)
    {
        result += sha1(fileContents.substr(i, pieceLengthInBytes));
    }

    this->pieceLengthInBytes = pieceLengthInBytes;
    this->concatenatedHashes = move(result);
}

string Pieces::toString() const
{
    return this->concatenatedHashes;
}
