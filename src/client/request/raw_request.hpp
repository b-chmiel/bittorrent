#pragma once

#include "url.hpp"
#include <optional>
#include <string>

namespace client::request
{
struct RawRequest
{
    virtual std::optional<std::string> send(const std::string& message) const = 0;
    virtual ~RawRequest() = default;
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