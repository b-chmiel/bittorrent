#include "tracker/request.hpp"
#include <boost/test/unit_test.hpp>

using namespace tracker;

BOOST_AUTO_TEST_SUITE(TestTrackerRequest)

BOOST_AUTO_TEST_CASE(ConstructWithoutUrlEncode)
{
    TrackerRequest req("a", "b", 1, 2, 3, 4, "c");
    BOOST_CHECK_EQUAL(req.toUrl("d"), "d?info_hash=a&peer_id=b&port=1&uploaded=2&downloaded=3&left=4&compact=1&event=c");
}

BOOST_AUTO_TEST_SUITE_END()