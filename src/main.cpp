#include "channels.hpp"
#include "downloader.hpp"
#include "execOptions.hpp"
#include "exitCode.hpp"
#include "threadUtilities.hpp"
#include "trie.hpp"
#include <functional>
#include <iostream>
#include <thread>


const std::string config = "./data/executable.opts.json";

auto main() -> int {
    int returnStatus = Success;
    execOptions dataAndDirectoryOptions;

    // Filling Configuration file
    try{
        // Filling the executable options
        std::cout << "The Program is right now trying to fill the executable options" << std::endl;
        dataAndDirectoryOptions.fill(config, returnStatus);
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
        return returnStatus;
    }

    Channels channels;
    // Found this interesting behaviour https://stackoverflow.com/a/65358074/13496837
    std::thread fillChannelAndMix(
            fillAndMix,
            std::ref(channels),
            std::cref(dataAndDirectoryOptions.getChannelsPath()),
            std::ref(returnStatus)
    );

    Downloader downloader;
    std::thread fillDownloader(
            &Downloader::fill,
            &downloader,
            std::cref(dataAndDirectoryOptions.getDownloaderPath()),
            std::ref(returnStatus)
    );

    Trie* trie = new Trie();
    std::thread trieMaker(
            populateTrie,
            trie,
            std::cref((dataAndDirectoryOptions.getArchiveNamePath())),
            std::ref(returnStatus)
    );

    fillChannelAndMix.join();
    fillDownloader.join();
    trieMaker.join();

    //TODO: Safe Trie operations and comparison against the archive file
    //TODO: start with playlist operation - complete and save and all safety.
    //TODO: Investigate the operations regarding JS/Python YT playlist updates
    return returnStatus;
}
