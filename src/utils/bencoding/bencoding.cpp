#include "bencoding.hpp"
#include <boost/variant.hpp>
#include <cctype>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

using namespace utils::bencoding;

Bencoding::Bencoding()
    : data(recursive_map())
{
}

Bencoding::Bencoding(int data)
    : data(data)
{
}

Bencoding::Bencoding(const std::string& data)
    : data(data)
{
}

Bencoding::Bencoding(const std::vector<std::string>& vec)
{
    this->data = recursive_vector();

    for (const auto& el : vec)
    {
        boost::get<recursive_vector>(this->data).push_back(Bencoding(el));
    }
}

Bencoding::Bencoding(const std::vector<Bencoding>& vec)
{
    this->data = recursive_vector();

    for (const auto& el : vec)
    {
        boost::get<recursive_vector>(this->data).push_back(el);
    }
}

void Bencoding::insert(const std::string& key, const Bencoding& value)
{
    if (this->data.type() != typeid(recursive_map))
    {
        throw std::runtime_error("Cannot insert to map");
    }

    boost::get<recursive_map>(this->data)[key] = value;
}

Bencoding Bencoding::operator[](const std::string& key) const
{
    if (this->data.type() == typeid(recursive_map))
    {
        auto map = boost::get<recursive_map>(this->data);
        if (map.contains(key))
        {
            return boost::get<recursive_map>(this->data).at(key).get();
        }

        return Bencoding();
    }

    return Bencoding();
}

Bencoding::operator int() const
{
    if (this->data.type() == typeid(int))
    {
        return boost::get<int>(this->data);
    }

    return 0u;
}

Bencoding::operator std::string() const
{
    if (this->data.type() == typeid(std::string))
    {
        return boost::get<std::string>(this->data);
    }

    return "";
}

Bencoding::operator std::vector<std::string>() const
{
    std::vector<std::string> result {};

    if (this->data.type() == typeid(recursive_vector))
    {
        auto vecBenc = boost::get<recursive_vector>(this->data);

        for (const auto& el : vecBenc)
        {
            result.push_back(static_cast<std::string>(el.get()));
        }

        return result;
    }

    return result;
}