#pragma once

#include <string>

namespace torrent
{
using namespace std;

class Pieces
{
public:
    Pieces(string contents, uint pieceLengthInBytes);
    Pieces() = default;

    string toString() const;
    uint pieceLengthInBytes;

private:
    string concatenatedHashes;
};
}