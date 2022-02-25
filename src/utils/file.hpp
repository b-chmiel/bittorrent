#pragma once

#include <string>

namespace utils::file
{
std::string readFile(const std::string& fileName);
void saveFile(const std::string& content, const std::string& fileName);
}