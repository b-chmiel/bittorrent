#pragma once

#include "url.hpp"
#include <optional>
#include <string>

namespace tracker::request
{
struct RawRequest
{
    virtual std::optional<std::string> send(const std::string& message) const = 0;
};

class RawRequestImpl final : public RawRequest
{
public:
    explicit RawRequestImpl(const std::string& url, int port);
    std::optional<std::string> send(const std::string& message) const override;

private:
    const std::string url;
    const int port;
};
}