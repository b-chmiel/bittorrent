#include "str.hpp"
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace utils;

vector<string> str::split(const string& str, const string& at)
{
    vector<string> result;
    boost::split(result, str, boost::is_any_of(at));
    return result;
}