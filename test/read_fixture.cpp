#include "read_fixture.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

std::string fixtures::read(const std::string& fileName)
{
    const std::string folder = "fixtures/";
    std::ifstream t(folder + fileName);
    if (t.fail())
    {
        throw std::runtime_error("Could not find file: " + folder + fileName);
        return "";
    }

    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}
