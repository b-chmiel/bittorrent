#include "client/handshake.hpp"
#include "client/peer.hpp"
#include "client/request/raw_request.hpp"
#include "client/utils/id.hpp"
#include "utils/utils.hpp"
#include <boost/test/unit_test.hpp>
#include <fakeit.hpp>
#include <iostream>
#include <string>

BOOST_AUTO_TEST_SUITE(TestHandshake)

BOOST_AUTO_TEST_CASE(ToString)
{
    const std::string infoHash = utils::sha::sha1("asdf");
    const std::string peerId = client::id::generate();
    const client::Handshake h(infoHash, peerId);

    const std::string actual = h.toString();

    const auto pstrlenLen = 1;
    const auto pstrLen = 19;
    const auto reservedLen = 8;
    const auto infoHashLen = 20;
    const auto peerIdLen = 20;
    BOOST_CHECK_EQUAL(actual.length(), pstrlenLen + pstrLen + reservedLen + infoHashLen + peerIdLen);
}

BOOST_AUTO_TEST_CASE(Send)
{
    using namespace fakeit;

    Mock<client::request::RawRequest> mock;
    When(Method(mock, send)).Return("message");

    const std::string infoHash = utils::sha::sha1("asdf");
    const std::string peerId = client::id::generate();
    const client::Handshake h(infoHash, peerId);

    const auto response = h.send(mock.get());
    BOOST_CHECK_EQUAL(response.value().raw, "message");
}

BOOST_AUTO_TEST_SUITE_END()