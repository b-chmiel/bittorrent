#include "read_fixture.hpp"
#include "torrent.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/test/unit_test.hpp>
#include <optional>
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

void test(const Data& data)
{
    auto sampleFile = fixtures::read(data.fileName);
    auto info = torrent::Info {
        .pieces = torrent::Pieces(sampleFile, data.pieceLength),
        .fileName = data.fileName,
        .lengthInBytes = data.lengthInBytes
    };

    auto announce = "http://127.0.0.1:6969/announce";
    auto announceList = nullopt;
    auto creationDate = data.creationDate;
    auto comment = nullopt;
    auto createdBy = "Enhanced-CTorrent/dnh3.3.2";

    torrent::Torrent file(info, announce, announceList, creationDate, comment, createdBy);

    vector<string> actual;
    boost::split(actual, file.toString(), boost::is_any_of(":"));

    vector<string> expected;
    boost::split(expected, fixtures::read(data.fileName + string(".torrent")), boost::is_any_of(":"));
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(Encode)
{
    test({ .fileName = "sample16M", .pieceLength = 262144, .lengthInBytes = 16777216, .creationDate = 1644744842 });
    test({ .fileName = "sample", .pieceLength = 262144, .lengthInBytes = 512, .creationDate = 1644712129 });
    test({ .fileName = "sample_odd_blocks", .pieceLength = 262144, .lengthInBytes = 12428588, .creationDate = 1644748464 });
}

BOOST_AUTO_TEST_SUITE_END()
