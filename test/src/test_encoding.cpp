#include "bencoding/bencoding.hpp"
#include <boost/test/unit_test.hpp>
#include <set>
#include <string>
#include <vector>

using namespace torrent::bencoding;
using namespace std;

BOOST_AUTO_TEST_SUITE(BencodingEncoding)

BOOST_AUTO_TEST_CASE(EncodeStrings)
{
    Bencoding::TorrentDict result = {
        { "announce", "asdf.asdf" },
        { "empty", "" },
    };
    BOOST_CHECK_EQUAL(Bencoding::encode(result), "d8:announce9:asdf.asdf5:empty0:e");
}

BOOST_AUTO_TEST_CASE(EncodeIntegers)
{
    Bencoding::TorrentDict result = {
        { "num", 123u },
        { "zero", 0u },
    };

    BOOST_CHECK_EQUAL(Bencoding::encode(result), "d3:numi123e4:zeroi0ee");
}

BOOST_AUTO_TEST_CASE(EncodeLists)
{
    vector<string> vec = { "spam", "eggs" };
    vector<string> vecEmpty = {};

    Bencoding::TorrentDict result = {
        { "vector", vec },
        { "vectorEmpty", vecEmpty },
    };

    BOOST_CHECK_EQUAL(Bencoding::encode(result), "d6:vectorl4:spam4:eggse11:vectorEmptylee");
}

BOOST_AUTO_TEST_CASE(EncodeDictionaries)
{
    typedef map<string, variant<string, uint>> map_var;
    map_var mapStr = { { "one", "one" }, { "two", "two" } };
    map_var mapInt = { { "one", 1u }, { "two", 2u } };

    Bencoding::TorrentDict result = {
        { "str", mapStr },
        { "int", mapInt },
    };

    BOOST_CHECK_EQUAL(Bencoding::encode(result), "d3:intd3:onei1e3:twoi2ee3:strd3:one3:one3:two3:twoee");
}

BOOST_AUTO_TEST_SUITE_END()
