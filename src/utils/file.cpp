#include "file.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
using namespace utils;

string file::readFile(const string& fileName)
{
    ifstream t(fileName);
    if (t.fail())
    {
        stringstream error;
        error << "Could not find file: ";
        error << fileName;
        error << ". Current directory: ";
        error << filesystem::current_path();
        throw runtime_error(error.str());
    }

    stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

void file::saveFile(const string& content, const string& fileName)
{
    ofstream file;
    file.open(fileName);
    file << content;
    if (file.fail())
    {
        throw runtime_error("Could not save file: " + fileName);
    }

    file.close();
}