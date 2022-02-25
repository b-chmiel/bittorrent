#pragma once

#include <string>

namespace torrent
{
class Pieces
{
public:
    Pieces(std::string contents, int pieceLengthInBytes);
    Pieces(const std::string& concatenatedHashes);
    Pieces() = default;

    std::string toString() const;
    int pieceLengthInBytes;
    friend auto operator<=>(const Pieces&, const Pieces&) = default;

private:
    std::string concatenatedHashes;
    std::string sha1(const std::string&) const;
};
}