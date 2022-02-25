#include "urlencode.hpp"
#include <cctype>
#include <iomanip>
#include <set>
#include <sstream>
#include <string>

const std::set<char> additionalAllowed = { '-', '_', '.', '~' };

std::string tracker::encode(const std::string& other)
{
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (const auto ch : other)
    {
        if (std::isalnum(ch) || additionalAllowed.contains(ch))
        {
            escaped << ch;
            continue;
        }

        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int(static_cast<unsigned char>(ch));
        escaped << std::nouppercase;
    }

    return escaped.str();
}