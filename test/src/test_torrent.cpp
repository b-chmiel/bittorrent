#include "torrent/torrent.hpp"
#include "utils/utils.hpp"
#include <boost/test/unit_test.hpp>
#include <vector>

BOOST_AUTO_TEST_SUITE(TorrentParser)

using namespace std;

struct Data
{
    string fileName;
    uint pieceLength;
    uint lengthInBytes;
    uint creationDate;
};

void test_encode(const Data& data)
{
    auto sampleFile = utils::readFile("fixtures/" + data.fileName);
    auto info = torrent::Info {
        .pieces = torrent::Pieces(sampleFile, data.pieceLength),
        .fileName = data.fileName,
        .lengthInBytes = data.lengthInBytes
    };

    auto announce = "http://127.0.0.1:6969/announce";
    vector<string> announceList {};
    auto creationDate = data.creationDate;
    auto comment = "";
    auto createdBy = "Enhanced-CTorrent/dnh3.3.2";

    torrent::Torrent file(info, announce, announceList, creationDate, comment, createdBy);

    auto actual = utils::split(file.toString(), ":");
    auto expected = utils::split(utils::readFile("fixtures/" + data.fileName + string(".torrent")), ":");
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(Encode)
{
    test_encode({ .fileName = "sample16M", .pieceLength = 262144, .lengthInBytes = 16777216, .creationDate = 1644744842 });
    test_encode({ .fileName = "sample", .pieceLength = 262144, .lengthInBytes = 512, .creationDate = 1644712129 });
    test_encode({ .fileName = "sample_odd_blocks", .pieceLength = 262144, .lengthInBytes = 12428588, .creationDate = 1644748464 });
}

void test_decode(const Data& data)
{
    auto fileName = "fixtures/" + data.fileName + ".torrent";
    torrent::Torrent actual(utils::readFile(fileName));

    auto info = torrent::Info {
        .pieces = torrent::Pieces(utils::readFile("fixtures/" + data.fileName), data.pieceLength),
        .fileName = data.fileName,
        .lengthInBytes = data.lengthInBytes
    };

    auto announce = "http://127.0.0.1:6969/announce";
    vector<string> announceList {};
    auto creationDate = data.creationDate;
    auto comment = "";
    auto createdBy = "Enhanced-CTorrent/dnh3.3.2";

    torrent::Torrent expected(info, announce, announceList, creationDate, comment, createdBy);

    BOOST_CHECK(actual == expected);
}

BOOST_AUTO_TEST_CASE(Decode)
{
    test_decode({ .fileName = "sample16M", .pieceLength = 262144, .lengthInBytes = 16777216, .creationDate = 1644744842 });
    test_decode({ .fileName = "sample", .pieceLength = 262144, .lengthInBytes = 512, .creationDate = 1644712129 });
    test_decode({ .fileName = "sample_odd_blocks", .pieceLength = 262144, .lengthInBytes = 12428588, .creationDate = 1644748464 });
}

BOOST_AUTO_TEST_SUITE_END()
