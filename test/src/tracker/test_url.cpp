#include "tracker/http_request/url.hpp"
#include <boost/test/unit_test.hpp>

using namespace tracker;

BOOST_AUTO_TEST_SUITE(TestUrl)

BOOST_AUTO_TEST_CASE(ParseWithoutPortHttp)
{
    Url url("http://asdf.com/announce");
    BOOST_CHECK_EQUAL(url.scheme, "http");
    BOOST_CHECK_EQUAL(url.host, "asdf.com");
    BOOST_CHECK_EQUAL(url.path, "/announce");
    BOOST_CHECK_EQUAL(url.port, 80);
}

BOOST_AUTO_TEST_CASE(ParseWithoutPortHttps)
{
    Url url("https://asdf.com/announce");
    BOOST_CHECK_EQUAL(url.scheme, "https");
    BOOST_CHECK_EQUAL(url.host, "asdf.com");
    BOOST_CHECK_EQUAL(url.path, "/announce");
    BOOST_CHECK_EQUAL(url.port, 443);
}

BOOST_AUTO_TEST_CASE(ParseWithPort)
{
    Url url("http://localhost:8000/announce");
    BOOST_CHECK_EQUAL(url.scheme, "http");
    BOOST_CHECK_EQUAL(url.host, "localhost");
    BOOST_CHECK_EQUAL(url.path, "/announce");
    BOOST_CHECK_EQUAL(url.port, 8000);
}

BOOST_AUTO_TEST_SUITE_END()