#include "logging.hpp"
#include <spdlog/spdlog.h>

using namespace utils;

void logging::info(const std::string& msg)
{
    spdlog::info(msg);
}

void logging::warn(const std::string& msg)
{
    spdlog::warn(msg);
}

void logging::error(const std::string& msg)
{
    spdlog::critical(msg);
}

void logging::debug(const std::string& msg)
{
    spdlog::debug(msg);
}