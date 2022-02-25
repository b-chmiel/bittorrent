#include "bencoding.hpp"

using namespace utils::bencoding;

class EncodeVisitor : public boost::static_visitor<std::string>
{
public:
    std::string encode(const std::string& str) const
    {
        return std::to_string(str.length()) + ":" + str;
    }

    std::string encode(int number) const
    {
        return "i" + std::to_string(number) + "e";
    }

    std::string encode(const Bencoding& var) const
    {
        return boost::apply_visitor(EncodeVisitor(), var.data);
    }

    std::string encode(const recursive_map& dict) const
    {
        std::string result = "d";
        for (const auto& [key, value] : dict)
        {
            result += encode(key);
            result += encode(value.get());
        }
        result += "e";

        return result;
    }

    std::string encode(const recursive_vector& vector) const
    {
        std::string result = "l";
        for (const auto& el : vector)
        {
            result += encode(el.get());
        }
        result += "e";

        return result;
    }

    template <typename T>
    decltype(auto) operator()(T x) const
    {
        return encode(x);
    }
};

std::string Bencoding::toString() const
{
    return boost::apply_visitor(EncodeVisitor(), this->data);
}