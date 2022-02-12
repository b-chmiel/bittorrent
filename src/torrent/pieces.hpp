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

    const char* toString() const;
    uint pieceLengthInBytes;

private:
    string concatenatedHashes;
};
}