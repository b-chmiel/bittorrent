#include "torrent/bencoding/bencoding.hpp"
#include <boost/test/unit_test.hpp>
#include <set>
#include <string>
#include <vector>

using namespace torrent::bencoding;
using namespace std;

BOOST_AUTO_TEST_SUITE(BencodingEncoding)

BOOST_AUTO_TEST_CASE(EncodeStrings)
{
    Bencoding data;
    data.insert("announce", Bencoding("asdf.asdf"));
    data.insert("empty", Bencoding(""));

    BOOST_CHECK_EQUAL(data.toString(), "d8:announce9:asdf.asdf5:empty0:e");
}

BOOST_AUTO_TEST_CASE(EncodeIntegers)
{
    Bencoding data;
    data.insert("num", Bencoding(123u));
    data.insert("zero", Bencoding(0u));

    BOOST_CHECK_EQUAL(data.toString(), "d3:numi123e4:zeroi0ee");
}

BOOST_AUTO_TEST_CASE(EncodeLists)
{
    vector<string> vec = { "spam", "eggs" };
    vector<string> vecEmpty = {};

    Bencoding data;
    data.insert("vector", vec);
    data.insert("vectorEmpty", vecEmpty);

    BOOST_CHECK_EQUAL(data.toString(), "d6:vectorl4:spam4:eggse11:vectorEmptylee");
}

BOOST_AUTO_TEST_CASE(EncodeDictionaries)
{
    Bencoding mapStr;
    mapStr.insert("one", Bencoding("one"));
    mapStr.insert("two", Bencoding("two"));
    Bencoding mapInt;
    mapInt.insert("one", Bencoding(1u));
    mapInt.insert("two", Bencoding(2u));

    Bencoding data;
    data.insert("str", mapStr);
    data.insert("int", mapInt);

    BOOST_CHECK_EQUAL(data.toString(), "d3:intd3:onei1e3:twoi2ee3:strd3:one3:one3:two3:twoee");
}

BOOST_AUTO_TEST_SUITE_END()
