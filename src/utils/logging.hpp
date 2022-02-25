#pragma once

#include <string>

namespace utils::logging
{
void info(const std::string& msg);
void warn(const std::string& msg);
void error(const std::string& msg);
void debug(const std::string& msg);
}