#include "pieces.hpp"
#include <boost/uuid/detail/sha1.hpp>
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

    // Back to string
    char buf[41] = { 0 };

    for (int i = 0; i < 5; i++)
    {
        std::sprintf(buf + (i << 3), "%08x", hash[i]);
    }

    return std::string(buf);
}

Pieces::Pieces(string fileContents, uint pieceLengthInBytes)
{
    auto i = 0;
    string result = "";
    string piece;
    for (const auto ch : fileContents)
    {
        if (i % pieceLengthInBytes == 0)
        {
            piece = "";

            if (i == 0)
                continue;

            result += sha1(piece);
        }

        piece += ch;
        i++;
    }

    result += sha1(piece);
    this->pieceLengthInBytes = pieceLengthInBytes;
    this->concatenatedHashes = move(result);
}

const char* Pieces::toString() const
{
    return this->concatenatedHashes.data();
}
