#include "id.hpp"
#include <algorithm>
#include <climits>
#include <functional>
#include <random>
#include <string>
#include <vector>

// https://stackoverflow.com/questions/25298585/efficiently-generating-random-bytes-of-data-in-c11-14

using random_bytes_engine
    = std::independent_bits_engine<
        std::default_random_engine, CHAR_BIT, unsigned char>;

std::string tracker::id::generate()
{
    random_bytes_engine rbe;
    std::vector<unsigned char> data(20);
    std::generate(begin(data), end(data), std::ref(rbe));

    std::string result(data.begin(), data.end());
    return result;
}