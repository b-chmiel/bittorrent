#pragma once

#include <string>
#include <vector>

namespace utils
{
std::vector<std::string> split(const std::string& str, const std::string& at);

std::string readFile(const std::string& fileName);
void saveFile(const std::string& content, const std::string& fileName);
}