#include "handler.hpp"
#include "../torrent/torrent.hpp"
#include "../tracker/client.hpp"
#include "../utils/utils.hpp"
#include "args.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace cli;

void Handler::help()
{
}

void Handler::createFile(const Args& input)
{
    std::cout << input.input << std::endl;
    std::cout << input.clientUrl << std::endl;
    std::cout << input.output << std::endl;

    auto sampleFile = utils::file::readFile(input.input);
    auto info = torrent::Info {
        .pieces = torrent::Pieces(sampleFile, 262144),
        .fileName = input.input,
        .lengthInBytes = 512
    };

    auto announce = input.clientUrl;
    auto announceList = std::vector<std::string>();
    auto creationDate = 1644522607;
    auto comment = "";
    auto createdBy = "Bittorrent";

    torrent::Torrent file(info, announce, announceList, creationDate, comment, createdBy);
    utils::file::saveFile(file.toString(), input.output);
}

void Handler::seed(const Args& input)
{
    torrent::Torrent torrent(utils::file::readFile(input.input));

    std::cout << "Announce: " << torrent.announce << std::endl;
    std::cout << "Comment: " << torrent.comment << std::endl;
    std::cout << "Created by: " << torrent.createdBy << std::endl;
    std::cout << "Creation date: " << torrent.creationDate << std::endl;
    std::cout << "Info: filename: " << torrent.info.fileName << std::endl;
    std::cout << "Info: lengthInBytes: " << torrent.info.lengthInBytes << std::endl;

    tracker::Client client(torrent);
}