#include "cli/parse_args.hpp"
#include "torrent/pieces.hpp"
#include "torrent/torrent.hpp"
#include "utils.hpp"
#include <exception>
#include <iostream>

using namespace std;

int main(int ac, char** av)
{
    try
    {
        cli::Args input(ac, av);
        cout << input.input << endl;
        cout << input.clientUrl << endl;
        cout << input.output << endl;

        auto sampleFile = utils::readFile(input.input);
        auto info = torrent::Info {
            .pieces = torrent::Pieces(sampleFile, 262144),
            .fileName = input.input,
            .lengthInBytes = 512
        };

        auto announce = input.clientUrl;
        auto announceList = vector<std::string>();
        auto creationDate = 1644522607;
        auto comment = "";
        auto createdBy = "Enhanced-CTorrent/dnh3.3.2";

        torrent::Torrent file(info, announce, announceList, creationDate, comment, createdBy);
        utils::saveFile(file.toString(), input.output);
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
