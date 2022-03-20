#include "client/request/http_request.hpp"
#include "client/tracker_request.hpp"
#include <boost/test/unit_test.hpp>
#include <fakeit.hpp>

using namespace fakeit;
using namespace client;

BOOST_AUTO_TEST_SUITE(TestTrackerRequest)

BOOST_AUTO_TEST_CASE(Send)
{
    Mock<request::HttpRequest> mock;
    const request::HttpResponse mockedResponse = { .status = 0, .body = "" };
    std::string invokedWith {};
    // clang-format off
    When(Method(mock, get)).AlwaysDo([&](const std::string& str)
    {
        invokedWith = str;
        return mockedResponse;
    });
    // clang-format on

    const std::string infoHash = "a";
    const std::string peerId = "b";
    const int port = 1;
    const int uploadedBytes = 2;
    const int downloadedBytes = 3;
    const int leftBytes = 4;
    const int compact = 1;
    const std::string event = "c";
    const std::string announceUrl = "d";

    const TrackerRequest request(infoHash, peerId, port, uploadedBytes, downloadedBytes, leftBytes, event, announceUrl);
    const auto response = request.send(mock.get());

    BOOST_CHECK_EQUAL(invokedWith, "d?info_hash=a&peer_id=b&port=1&uploaded=2&downloaded=3&left=4&compact=1&event=c");
}

BOOST_AUTO_TEST_SUITE_END()