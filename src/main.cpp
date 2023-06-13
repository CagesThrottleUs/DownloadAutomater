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
    Downloader downloader;
    Trie* trie = new Trie();
    runAllThreadCommands(channels, downloader, trie, dataAndDirectoryOptions, returnStatus);

    //TODO: Safe Trie operations and comparison against the archive file
    //TODO: start with playlist operation - complete and save and all safety.
    //TODO: Investigate the operations regarding JS/Python YT playlist updates
    return returnStatus;
}
