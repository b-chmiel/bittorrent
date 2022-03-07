#include "pieces.hpp"
#include "../utils/sha.hpp"
#include <stddef.h>
#include <string>
#include <utility>

using namespace torrent;

Pieces::Pieces(const std::string& _concatenatedHashes)
    : concatenatedHashes(_concatenatedHashes)
{
}

Pieces::Pieces(const std::string& fileContents, int _pieceLengthInBytes)
    : pieceLengthInBytes(_pieceLengthInBytes)
{
    const auto pieceLength = static_cast<size_t>(this->pieceLengthInBytes);
    for (size_t i = 0; i < fileContents.size(); i += pieceLength)
    {
        this->concatenatedHashes += utils::sha::sha1(fileContents.substr(i, pieceLength));
    }
}

std::string Pieces::toString() const
{
    return this->concatenatedHashes;
}
