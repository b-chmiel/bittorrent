#pragma once

#include "args.hpp"

namespace cli
{
class Handler
{
public:
    static void createFile(const Args&);
    static void seed(const Args&);
};
}