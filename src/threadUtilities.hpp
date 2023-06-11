//
// Created by CagesThrottleUs on 11-06-2023.
//

#ifndef DOWNLOADAUTOMATER_THREADUTILITIES_HPP
#define DOWNLOADAUTOMATER_THREADUTILITIES_HPP

#include "channels.hpp"
#include "trie.hpp"

void fillAndMix(Channels& channels, const std::string& path, int& retStatus);

void populateTrie(Trie* trie,const std::string& path, int &retStatus);

#endif //DOWNLOADAUTOMATER_THREADUTILITIES_HPP
