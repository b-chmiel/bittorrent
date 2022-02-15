#include "torrent/bencoding/bencoding.hpp"
#include "utils/utils.hpp"
#include <boost/test/unit_test.hpp>
#include <set>
#include <string>
#include <vector>

using namespace torrent::bencoding;
using namespace std;

BOOST_AUTO_TEST_SUITE(BencodingDecode)

BOOST_AUTO_TEST_CASE(Decode)
{
    //    typedef map<string, variant<string, uint>> map_var;
    //
    //    Bencoding::TorrentDict expected = {};
    //    auto file = utils::readFile("fixtures/sample.torrent");
    //    auto actual = Bencoding::decode(file);
    //
    //    for (const auto& [key, value] : actual)
    //    {
    //        auto expectedEl = expected[key];
    //        if (holds_alternative<map_var>(value) && holds_alternative<map_var>(expectedEl))
    //        {
    //            for (const auto& [innerKey, innerValue] : get<map_var>(value))
    //            {
    //                auto innerExpected = get<map_var>(expectedEl);
    //                BOOST_CHECK_EQUAL(get<uint>(innerValue), get<uint>(innerExpected[innerKey]));
    //            }
    //        }
    //    }
    // BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
    // BOOST_FAIL(true);
}

BOOST_AUTO_TEST_SUITE_END()
