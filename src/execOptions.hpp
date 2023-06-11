//
// Created by CagesThrottleUs on 09-06-2023.
//

#ifndef DOWNLOADAUTOMATER_EXECOPTIONS_HPP
#define DOWNLOADAUTOMATER_EXECOPTIONS_HPP


#include "execDataOptions.hpp"
#include <string>
#include <vector>

class execOptions {
    std::vector<std::string> directories;
    execDataOptions execDataOptions;
public:
    explicit execOptions();
    void fill(const std::string& srcLocation, int &retStatus);
    auto getChannelsPath() -> const std::string&;
    auto getDownloaderPath() -> const std::string&;
    auto getArchiveLinkPath() -> const std::string&;
    auto getArchiveNamePath() -> const std::string&;
    auto getGeneratorNamePath() -> const std::string&;
};


#endif //DOWNLOADAUTOMATER_EXECOPTIONS_HPP
