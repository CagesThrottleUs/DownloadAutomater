//
// Created by CagesThrottleUs on 11-06-2023.
//

#include "threadUtilities.hpp"
#include <iostream>

void fillAndMix(Channels& channels, const std::string& path, int& retStatus){
    try{
        std::cout << "The Program is right now trying to fill the channel information!" << std::endl;
        channels.fill(path, retStatus);
    } catch(const std::exception& exception){
        std::cout << exception.what() << std::endl;
        return;
    }
    channels.mix();
}

void populateTrie(Trie* trie,const std::string& path, int &retStatus){
    try{
        trie->fill(path, retStatus);
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
        return;
    }
}