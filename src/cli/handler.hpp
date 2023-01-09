#pragma once

#include "args.hpp"

namespace cli
{
class Handler
{
public:
    static int createFile(const Args&);
    static int seed(const Args&);
};
}