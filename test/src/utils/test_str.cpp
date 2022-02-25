#include "utils/utils.hpp"
#include <boost/test/unit_test.hpp>
#include <vector>

BOOST_AUTO_TEST_SUITE(TestStr)

BOOST_AUTO_TEST_CASE(Split)
{
    auto result = utils::str::split("asdf.fdsa.1234.4321", ".");
    std::vector<std::string> expected = { "asdf", "fdsa", "1234", "4321" };
    BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()