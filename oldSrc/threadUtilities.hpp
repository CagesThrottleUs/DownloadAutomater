//
// Created by CagesThrottleUs on 11-06-2023.
//

#ifndef DOWNLOADAUTOMATER_THREADUTILITIES_HPP
#define DOWNLOADAUTOMATER_THREADUTILITIES_HPP

#include "channels.hpp"
#include "downloader.hpp"
#include "execOptions.hpp"
#include "trie.hpp"

void fillAndMix(Channels& channels, const std::string& path, int& retStatus);
void populateTrie(Trie* trie,const std::string& path, int &retStatus);
void runAllThreadCommands(Channels &channels,Downloader& downloader, Trie* trie, execOptions& execData, int& returnStatus);

#endif //DOWNLOADAUTOMATER_THREADUTILITIES_HPP
