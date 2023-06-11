#ifndef DOWNLOADAUTOMATER_EXECDATAOPTIONS_HPP
#define DOWNLOADAUTOMATER_EXECDATAOPTIONS_HPP

//
// Created by CagesThrottleUs on 09-06-2023.
//

#include "json.hpp"
#include <string>
#include <unordered_map>
using json = nlohmann::json;

class execDataOptions {
    std::string channelsJson;
    std::string downloaderJson;
    std::unordered_map<std::string, std::string> archives;
    std::unordered_map<std::string, std::string> generators;
public:
    void fill(const json& harvestedData, int &retStatus, const std::string &srcLocation);

    // Getters
    auto getChannelsJson() const -> const std::string &;
    auto getDownloaderJson() const -> const std::string &;
    auto getArchiveFileName(const std::string& key) -> const std::string&;
    auto getGeneratorFileName(const std::string& key) -> const std::string&;

private:
    auto matchArchivesAndGeneratorKeys() -> bool;
};


#endif //DOWNLOADAUTOMATER_EXECDATAOPTIONS_HPP
