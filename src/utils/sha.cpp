#include "sha.hpp"
#include <boost/uuid/detail/sha1.hpp>
#include <string>

using namespace utils;

std::string sha::sha1(const std::string& str)
{
    // https://stackoverflow.com/questions/28489153/how-to-portably-compute-a-sha1-hash-in-c
    boost::uuids::detail::sha1 sha1;
    sha1.process_bytes(str.data(), str.size());
    unsigned hash[5] = { 0 };
    sha1.get_digest(hash);

    std::string result {};
    for (const auto ch : hash)
    {
        for (int j = sizeof(hash[0]) - 1; j >= 0; j--)
        {
            result += static_cast<char>((ch & (255u << j * 8)) >> j * 8);
        }
    }

    return result;
}