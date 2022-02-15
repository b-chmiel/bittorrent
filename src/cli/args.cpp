#include "args.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <map>
#include <string>

using namespace cli;

namespace po = boost::program_options;

const std::map<Option, const char*>
    optionNames = {
        { Option::HELP, "help" },
        { Option::INPUT, "input" },
        { Option::CLIENT_URL, "client-url" },
        { Option::OUTPUT, "output" }
    };

Args::Args(int ac, char** av)
{
    po::options_description description("Allowed options");
    // clang-format off
        description.add_options()
            (optionNames.at(Option::HELP), "produce help message")
            (optionNames.at(Option::INPUT), po::value<std::string>(), "input filename")
            (optionNames.at(Option::CLIENT_URL), po::value<std::string>(), "client url")
            (optionNames.at(Option::OUTPUT), po::value<std::string>(), "output torrent file");
    // clang-format on

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, description), vm);
    po::notify(vm);

    if (vm.count(optionNames.at(Option::HELP)))
    {
        this->mode = CliMode::HELP;
        std::cout << description << "\n";
        return;
    }
    else if (ac == 2)
    {
        this->mode = CliMode::SEED;
        this->input = av[1];
        return;
    }
    else
    {
        this->mode = CliMode::CREATE_FILE;
        this->input = "";
        this->clientUrl = "http://127.0.0.1:9999";
        this->output = "";

        if (vm.count(optionNames.at(Option::INPUT)))
        {
            this->input = vm[optionNames.at(Option::INPUT)].as<std::string>();
        }
        else
        {
            throw std::runtime_error("input is required");
        }

        if (vm.count(optionNames.at(Option::CLIENT_URL)))
        {
            this->clientUrl = vm[optionNames.at(Option::CLIENT_URL)].as<std::string>();
        }

        if (vm.count(optionNames.at(Option::OUTPUT)))
        {
            this->output = vm[optionNames.at(Option::OUTPUT)].as<std::string>();
        }
        else
        {
            this->output = this->input + ".torrent";
        }
    }
}
