#include "pieces.hpp"
#include <boost/uuid/detail/sha1.hpp>
#include <cmath>
#include <string>

using namespace torrent;

Pieces::Pieces(const std::string& concatenatedHashes)
    : concatenatedHashes(concatenatedHashes)
{
}

Pieces::Pieces(std::string fileContents, uint pieceLengthInBytes)
{
    auto i = 0;
    std::string result {};
    std::string piece {};
    for (int i = 0; i < fileContents.size(); i += pieceLengthInBytes)
    {
        result += sha1(fileContents.substr(i, pieceLengthInBytes));
    }

    this->pieceLengthInBytes = pieceLengthInBytes;
    this->concatenatedHashes = std::move(result);
}

std::string Pieces::toString() const
{
    return this->concatenatedHashes;
}

std::string Pieces::sha1(const std::string& str) const
{
    // https://stackoverflow.com/questions/28489153/how-to-portably-compute-a-sha1-hash-in-c
    boost::uuids::detail::sha1 sha1;
    sha1.process_bytes(str.data(), str.size());
    unsigned hash[5] = { 0 };
    sha1.get_digest(hash);

    std::string result {};
    for (const auto ch : hash)
    {
        for (int j = sizeof(hash[0]) - 1; j >= 0; j--)
        {
            result += (char)((ch & (255 << j * 8)) >> j * 8);
        }
    }

    return std::move(result);
}
