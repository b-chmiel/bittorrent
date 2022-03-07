#include "torrent/pieces.hpp"
#include "utils/sha.hpp"
#include <boost/test/unit_test.hpp>
#include <string>
#include <vector>

BOOST_AUTO_TEST_SUITE(Pieces)

BOOST_AUTO_TEST_CASE(FromFile)
{
    const std::string contents = "1234567890";

    constexpr auto pieceLen = sizeof(char);
    const torrent::Pieces pieces(contents, pieceLen);
    std::string expected {};

    for (size_t i = 0; i < contents.size(); ++i)
    {
        expected += utils::sha::sha1(contents.substr(i, 1));
    }

    BOOST_CHECK_EQUAL(pieces.toString(), expected);
}

BOOST_AUTO_TEST_SUITE_END()
