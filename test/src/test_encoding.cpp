#include "encoding.hpp"
#include <boost/test/unit_test.hpp>
#include <set>
#include <string>
#include <vector>

using namespace torrent;
using namespace std;

BOOST_AUTO_TEST_SUITE(BencodingEncoding)

BOOST_AUTO_TEST_CASE(EncodeStrings)
{
    BOOST_CHECK_EQUAL(Encoding::encode("announce"), "8:announce");
    BOOST_CHECK_EQUAL(Encoding::encode(""), "0:");
}

BOOST_AUTO_TEST_CASE(EncodeIntegers)
{
    BOOST_CHECK_EQUAL(Encoding::encode(123512), "i123512e");
    BOOST_CHECK_EQUAL(Encoding::encode(-123512), "i-123512e");
    BOOST_CHECK_EQUAL(Encoding::encode(-0), "i0e");
    BOOST_CHECK_EQUAL(Encoding::encode(0), "i0e");
}

BOOST_AUTO_TEST_CASE(EncodeLists)
{
    BOOST_CHECK_EQUAL(Encoding::encode(vector<string> { "spam", "eggs" }), "l4:spam4:eggse");
    BOOST_CHECK_EQUAL(Encoding::encode(vector<string> {}), "le");
    BOOST_CHECK_EQUAL(Encoding::encode(vector<string> { "e", "e", "e", "e" }), "l1:e1:e1:e1:ee");
    BOOST_CHECK_EQUAL(Encoding::encode(vector<string> { "1", "2" }), "l1:11:2e");
}

BOOST_AUTO_TEST_CASE(EncodeDictionaries)
{
    BOOST_FAIL(false);
}

BOOST_AUTO_TEST_SUITE_END()
