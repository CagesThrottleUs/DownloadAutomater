//
// Created by CagesThrottleUs on 15-06-2023.
//

#ifndef DOWNLOADAUTOMATER_PLAYLIST_HPP
#define DOWNLOADAUTOMATER_PLAYLIST_HPP


#include "downloader.hpp"
#include "trie.hpp"
#include <string>

class Playlist {
    bool execute{false};
    std::string defaultLink{};
    std::string tempOutputFolder{};
    bool safeMode{false};
    std::string finalMoveLocation{};
    std::string shellLocation{};
    std::string shellFileName{};
    std::string shellFileNameSafe{};

public:
    Playlist();
    void fill(const std::string& srcLocation, int& retStatus);
    void download(Downloader &downloader, int &retStatus, Trie* trie);
    [[nodiscard]] auto isExecute() const -> bool;

private:
    auto checkLinkFormation() -> bool;
};


#endif //DOWNLOADAUTOMATER_PLAYLIST_HPP
