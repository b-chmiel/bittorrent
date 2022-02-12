#include "cli/parse_args.hpp"
#include "torrent/pieces.hpp"
#include "torrent/torrent.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

std::string readFile(const std::string& fileName)
{
    std::ifstream t(fileName);
    if (t.fail())
    {
        throw std::runtime_error("Could not find file: " + fileName);
    }

    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

void saveFile(const std::string& content, const std::string& fileName)
{
    std::ofstream file;
    file.open(fileName);
    file << content;
    if (file.fail())
    {
        throw std::runtime_error("Could not save file: " + fileName);
    }

    file.close();
}

int main(int ac, char** av)
{
    try
    {
        cli::Args input(ac, av);
        std::cout << input.input << std::endl;
        std::cout << input.clientUrl << std::endl;
        std::cout << input.output << std::endl;

        auto sampleFile = readFile(input.input);
        auto info = torrent::Info {
            .pieces = torrent::Pieces(sampleFile, 262144),
            .fileName = input.input,
            .lengthInBytes = 512
        };

        auto announce = input.clientUrl;
        auto announceList = std::nullopt;
        auto creationDate = 1644522607;
        auto comment = std::nullopt;
        auto createdBy = "Enhanced-CTorrent/dnh3.3.2";

        torrent::Torrent file(info, announce, announceList, creationDate, comment, createdBy);
        saveFile(file.toString(), input.output);
    }
    catch (std::exception& e)
    {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Exception of unknown type!\n";
        return 1;
    }
    return 0;
}
