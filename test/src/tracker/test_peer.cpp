#include "tracker/peer.hpp"
#include <boost/test/unit_test.hpp>

using namespace tracker;

BOOST_AUTO_TEST_SUITE(TestPeer)

BOOST_AUTO_TEST_CASE(ParsePeerInfo)
{
    Peer p("abcdef");
    BOOST_CHECK_EQUAL(p.url, "97.98.99.100:25958");
}

BOOST_AUTO_TEST_CASE(ParsePeerInfoFailing)
{
    char ip1 = 0x7F;
    char ip2 = 0x00;
    char ip3 = 0x00;
    char ip4 = 0x01;
    char port1 = 0x0A;
    char port2 = 0x92;

    std::stringstream ss;
    ss << ip1;
    ss << ip2;
    ss << ip3;
    ss << ip4;
    ss << port1;
    ss << port2;

    Peer p(ss.str());
    BOOST_CHECK_EQUAL(p.url, "127.0.0.1:2706");
}

BOOST_AUTO_TEST_SUITE_END()