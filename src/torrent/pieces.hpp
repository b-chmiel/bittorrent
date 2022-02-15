#pragma once

#include <string>

namespace torrent
{
class Pieces
{
public:
    Pieces(std::string contents, uint pieceLengthInBytes);
    Pieces(const std::string& concatenatedHashes);
    Pieces() = default;

    std::string toString() const;
    uint pieceLengthInBytes;
    friend auto operator<=>(const Pieces&, const Pieces&) = default;

private:
    std::string concatenatedHashes;
};
}