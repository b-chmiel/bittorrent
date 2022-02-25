#include "pieces.hpp"
#include "../utils/utils.hpp"
#include <cmath>
#include <string>

using namespace torrent;

Pieces::Pieces(const std::string& concatenatedHashes)
    : concatenatedHashes(concatenatedHashes)
{
}

Pieces::Pieces(std::string fileContents, int pieceLengthInBytes)
{
    const auto pieceLength = static_cast<size_t>(pieceLengthInBytes);
    std::string result {};
    std::string piece {};
    for (size_t i = 0; i < fileContents.size(); i += pieceLength)
    {
        result += utils::sha::sha1(fileContents.substr(i, pieceLength));
    }

    this->pieceLengthInBytes = pieceLengthInBytes;
    this->concatenatedHashes = std::move(result);
}

std::string Pieces::toString() const
{
    return this->concatenatedHashes;
}
