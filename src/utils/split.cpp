#include "utils.hpp"
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

using namespace std;

vector<string> utils::split(const string& str, const string& at)
{
    vector<string> result;
    boost::split(result, str, boost::is_any_of(at));
    return move(result);
}