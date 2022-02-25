#include "utils/utils.hpp"
#include <boost/test/unit_test.hpp>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

using namespace utils::bencoding;
using namespace std;

BOOST_AUTO_TEST_SUITE(BencodingDecode)

BOOST_AUTO_TEST_CASE(StringSuccess)
{
    auto bencoded = Bencoding::decode("8:contents");
    BOOST_CHECK_EQUAL(static_cast<string>(bencoded), "contents");
}

BOOST_AUTO_TEST_CASE(StringFailure)
{
    auto values = { ":contents", "999:asd", "999asdf" };

    for (const auto& value : values)
    {
        BOOST_TEST_MESSAGE("value: " << value);
        BOOST_CHECK_THROW(Bencoding::Bencoding::decode(value), exception);
    }
}

BOOST_AUTO_TEST_CASE(IntSuccess)
{
    auto bencoded = Bencoding::Bencoding::decode("i234e");
    BOOST_CHECK_EQUAL(static_cast<int>(bencoded), 234u);

    bencoded = Bencoding::Bencoding::decode("i0e");
    BOOST_CHECK_EQUAL(static_cast<int>(bencoded), 0u);
}

BOOST_AUTO_TEST_CASE(IntFailure)
{
    auto values = { "a", "i", "e", "ie", "ieee", "i0i", "i234" };

    for (const auto& value : values)
    {
        BOOST_TEST_MESSAGE("value: " << value);
        BOOST_CHECK_THROW(Bencoding::Bencoding::decode(value), exception);
    }
}

BOOST_AUTO_TEST_CASE(ListSuccess)
{
    auto bencoded = static_cast<vector<string>>(Bencoding::Bencoding::decode("l2:ss3:fds5:55555e"));
    vector<string> expected { "ss", "fds", "55555" };
    BOOST_CHECK_EQUAL_COLLECTIONS(bencoded.begin(), bencoded.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(ListFailure)
{
    auto values = { "ll", "e", "lasdfe" };

    for (const auto& value : values)
    {
        BOOST_TEST_MESSAGE("value: " << value);
        BOOST_CHECK_THROW(Bencoding::Bencoding::decode(value), exception);
    }
}

BOOST_AUTO_TEST_SUITE_END()
