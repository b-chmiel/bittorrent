#include "tracker/utils/id.hpp"
#include "utils/file.hpp"
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <memory>
#include <stdexcept>

BOOST_AUTO_TEST_SUITE(TestFile)

BOOST_AUTO_TEST_CASE(Read)
{
    const auto filename = "asdf.txt";
    const auto content = "asdf";
    std::ofstream out(filename);
    out << content;
    out.close();

    BOOST_CHECK_EQUAL(utils::file::readFile(filename), content);
}

BOOST_AUTO_TEST_CASE(ReadFileThatDoesNotExist)
{
    const auto filename = tracker::id::generate();
    BOOST_CHECK_THROW(utils::file::readFile(filename), std::exception);
}

BOOST_AUTO_TEST_CASE(Save)
{
    const auto content = "asdf";
    const auto filename = "asdf.txt";
    utils::file::saveFile(content, filename);
    BOOST_CHECK_EQUAL(utils::file::readFile(filename), content);
}

BOOST_AUTO_TEST_SUITE_END()