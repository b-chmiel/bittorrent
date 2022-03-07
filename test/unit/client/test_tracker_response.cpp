#include "client/request/http_request.hpp"
#include "client/tracker_response.hpp"
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <string>
#include <utils/file.hpp>

using namespace tracker::request;

BOOST_AUTO_TEST_SUITE(TestTrackerResponse)

BOOST_AUTO_TEST_CASE(ConstructFromEmptyResponse)
{
    const HttpResponse httpResponse = { .status = 1, .body = "" };
    const tracker::TrackerResponse resp(httpResponse);

    const std::string expected = "{'failure reason': '', 'warning message': '', 'interval': 0, 'min interval': 0, 'tracker id': '', 'seeders': 0, 'leechers': 0, 'peers': []}";
    const std::string actual = resp.toString();
    BOOST_TEST(actual == expected);
}

BOOST_AUTO_TEST_CASE(ConstructFromMalformedResponse)
{
    const HttpResponse httpResponse = { .status = 1, .body = "asdf" };
    const tracker::TrackerResponse resp(httpResponse);

    const std::string expected = "{'failure reason': '', 'warning message': '', 'interval': 0, 'min interval': 0, 'tracker id': '', 'seeders': 0, 'leechers': 0, 'peers': []}";
    const std::string actual = resp.toString();
    BOOST_TEST(actual == expected);
}

BOOST_AUTO_TEST_CASE(ConstructFromResponseWithoutPeers)
{
    const HttpResponse httpResponse = { .status = 1, .body = "d8:completei1e10:downloadedi0e10:incompletei1e8:intervali1644e12:min intervali822e5:peers0:e" };
    const tracker::TrackerResponse resp(httpResponse);

    const std::string expected = "{'failure reason': '', 'warning message': '', 'interval': 1644, 'min interval': 822, 'tracker id': '', 'seeders': 1, 'leechers': 1, 'peers': []}";
    const std::string actual = resp.toString();
    BOOST_TEST(actual == expected);
}

BOOST_AUTO_TEST_CASE(ConstructFromResponseWithPeers)
{
    const auto responseBin = utils::file::readFile("fixtures/tracker_response.bin");
    const HttpResponse httpResponse = { .status = 1, .body = responseBin };
    const tracker::TrackerResponse resp(httpResponse);

    const std::string expected = "{'failure reason': '', 'warning message': '', 'interval': 1622, 'min interval': 811, 'tracker id': '', 'seeders': 2, 'leechers': 1, 'peers': [{'url': '127.0.0.1:6767'}, {'url': '127.0.0.1:2706'}, ]}";
    const std::string actual = resp.toString();
    BOOST_TEST(actual == expected);
}

BOOST_AUTO_TEST_SUITE_END()