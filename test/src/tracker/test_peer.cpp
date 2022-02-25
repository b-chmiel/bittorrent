#include "tracker/peer.hpp"
#include <boost/test/unit_test.hpp>

using namespace tracker;

BOOST_AUTO_TEST_SUITE(TestPeer)

BOOST_AUTO_TEST_CASE(ParsePeerInfo)
{
    Peer p("abcdef");
    BOOST_CHECK_EQUAL(p.url, "97.98.99.100:25958");
}

BOOST_AUTO_TEST_SUITE_END()