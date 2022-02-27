#include "cli/args.hpp"
#include "cli/handler.hpp"
#include <exception>
#include <iostream>

using namespace std;

int main(int ac, char** av)
{
    try
    {
        cli::Args input(ac, av);
        switch (input.mode)
        {
        case cli::CliMode::CREATE_FILE:
            cli::Handler::createFile(input);
            break;
        case cli::CliMode::SEED:
            cli::Handler::seed(input);
        case cli::CliMode::HELP:
            break;
        }
    }
    catch (exception& e)
    {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch (...)
    {
        cerr << "Exception of unknown type!\n";
        return 1;
    }
    return 0;
}
