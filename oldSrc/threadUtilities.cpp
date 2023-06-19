//
// Created by CagesThrottleUs on 11-06-2023.
//

#include "threadUtilities.hpp"
#include <iostream>
#include <thread>

void fillAndMix(Channels& channels, const std::string& path, int& retStatus){
    try{
//        std::cout << "The Program is right now trying to fill the channel information!" << std::endl;
        channels.fill(path, retStatus);
    } catch(const std::exception& exception){
        std::cout << exception.what() << std::endl;
        return;
    }
    channels.mix();
}

void populateTrie(Trie* trie, const std::string& path, int &retStatus){
    try{
        trie->fill(path, retStatus);
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
        return;
    }
}

void runAllThreadCommands(Channels &channels,Downloader& downloader, Trie* trie, execOptions& execData, int& returnStatus){

    // Found this interesting behaviour https://stackoverflow.com/a/65358074/13496837
    std::thread fillChannelAndMix(
            fillAndMix,
            std::ref(channels),
            std::cref(execData.getChannelsPath()),
            std::ref(returnStatus)
    );


    std::thread fillDownloader(
            &Downloader::fill,
            &downloader,
            std::cref(execData.getDownloaderPath()),
            std::ref(returnStatus)
    );


    std::thread trieMaker(
            populateTrie,
            trie,
            std::cref((execData.getArchiveNamePath())),
            std::ref(returnStatus)
    );

    std::thread directoryCreator(
            &execOptions::createDirectories,
            &execData
    );

    fillChannelAndMix.join();
    fillDownloader.join();
    trieMaker.join();
    directoryCreator.join();
}