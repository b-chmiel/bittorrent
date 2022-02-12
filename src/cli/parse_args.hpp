#pragma once

#include <map>
#include <string>

namespace cli
{
enum class Option
{
    HELP,
    INPUT,
    CLIENT_URL,
    OUTPUT
};

class Args
{
public:
    explicit Args(int ac, char** av);

    std::string input;
    std::string clientUrl;
    std::string output;
};
}