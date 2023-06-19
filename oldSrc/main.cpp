#include "channels.hpp"
#include "downloader.hpp"
#include "execOptions.hpp"
#include "exitCode.hpp"
#include "playlist.hpp"
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

    Playlist playlist;
    try{
        std::cout << "The Program is right now trying to execute Playlist Options" << std::endl;
        playlist.fill(config, returnStatus);
        if(playlist.isExecute()){
            playlist.download(downloader, returnStatus, trie);
        }
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
        return returnStatus;
    }

    return returnStatus;

    //TODO: This is getting messy - refactor every single file
    //TODO: GENERATE DOCUMENTATION for all in parallel
    //TODO: Redo files for executable options
}
