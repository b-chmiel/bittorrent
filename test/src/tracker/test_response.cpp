#include "tracker/http_request/http_request.hpp"
#include "tracker/tracker_response.hpp"
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <string>
#include <utils/file.hpp>

using namespace tracker;
namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(TestTrackerResponse)

BOOST_AUTO_TEST_CASE(ConstructFromEmptyResponse)
{
    HttpResponse httpResponse = { .status = 1, .body = "" };
    TrackerResponse resp(httpResponse);

    std::string expected = "{'failure reason': '', 'warning message': '', 'interval': 0, 'min interval': 0, 'tracker id': '', 'seeders': 0, 'leechers': 0, 'peers': []}";
    std::string actual = resp.toString();
    BOOST_TEST(actual == expected);
}

BOOST_AUTO_TEST_CASE(ConstructFromMalformedResponse)
{
    HttpResponse httpResponse = { .status = 1, .body = "asdf" };
    TrackerResponse resp(httpResponse);

    std::string expected = "{'failure reason': '', 'warning message': '', 'interval': 0, 'min interval': 0, 'tracker id': '', 'seeders': 0, 'leechers': 0, 'peers': []}";
    std::string actual = resp.toString();
    BOOST_TEST(actual == expected);
}

BOOST_AUTO_TEST_CASE(ConstructFromResponseWithoutPeers)
{
    HttpResponse httpResponse = { .status = 1, .body = "d8:completei1e10:downloadedi0e10:incompletei1e8:intervali1644e12:min intervali822e5:peers0:e" };
    TrackerResponse resp(httpResponse);

    std::string expected = "{'failure reason': '', 'warning message': '', 'interval': 1644, 'min interval': 822, 'tracker id': '', 'seeders': 1, 'leechers': 1, 'peers': []}";
    std::string actual = resp.toString();
    BOOST_TEST(actual == expected);
}

BOOST_AUTO_TEST_CASE(ConstructFromResponseWithPeers)
{
    auto responseBin = utils::file::readFile("fixtures/tracker_response.bin");
    HttpResponse httpResponse = { .status = 1, .body = responseBin };
    TrackerResponse resp(httpResponse);

    std::string expected = "{'failure reason': '', 'warning message': '', 'interval': 1622, 'min interval': 811, 'tracker id': '', 'seeders': 2, 'leechers': 1, 'peers': [{'url': '127.0.0.1:6767'}, {'url': '127.0.0.1:2706'}, ]}";
    std::string actual = resp.toString();
    BOOST_TEST(actual == expected);
}

BOOST_AUTO_TEST_SUITE_END()