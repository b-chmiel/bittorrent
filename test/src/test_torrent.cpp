#include "read_fixture.hpp"
#include "torrent.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/test/unit_test.hpp>
#include <optional>
#include <vector>

BOOST_AUTO_TEST_SUITE(TorrentParser)

BOOST_AUTO_TEST_CASE(Encode)
{
    auto sampleFile = fixtures::read("sample");
    auto info = torrent::Info {
        .pieces = torrent::Pieces(sampleFile, 262144),
        .fileName = "sample",
        .lengthInBytes = 512
    };

    auto announce = "http://127.0.0.1:9999";
    auto announceList = std::nullopt;
    auto creationDate = 1644522607;
    auto comment = std::nullopt;
    auto createdBy = "Enhanced-CTorrent/dnh3.3.2";

    torrent::Torrent file(info, announce, announceList, creationDate, comment, createdBy);

    std::vector<std::string> actual;
    boost::split(actual, file.toString(), boost::is_any_of(":"));

    std::vector<std::string> expected;
    boost::split(expected, fixtures::read("sample.torrent"), boost::is_any_of(":"));
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()
