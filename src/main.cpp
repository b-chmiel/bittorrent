#define BACKWARD_HAS_DW 1

#include "cli/args.hpp"
#include "cli/handler.hpp"
#include <backward.hpp>
#include <exception>
#include <iostream>

using namespace std;

backward::SignalHandling sh {};

int main(int ac, char** av)
{
    const cli::Args input(ac, av);
    switch (input.mode)
    {
    case cli::CliMode::CREATE_FILE:
        return cli::Handler::createFile(input);
    case cli::CliMode::SEED:
        return cli::Handler::seed(input);
    case cli::CliMode::HELP:
        return 0;
    default:
        return 1;
    }
}
