//
// Created by CagesThrottleUs on 09-06-2023.
//

#include "exitCode.hpp"
#include "execDataOptions.hpp"
#include "jsonKeyValueNotFoundException.hpp"
#include "keyValuePairMismatchException.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_set>

void execDataOptions::fill(const json& harvestedData, int &retStatus, const std::string &srcLocation) {
    std::string keyName;
    try{
        // Fill Channels JSON
        std::cout << "\nFinding the Channels Data JSON file" << std::endl;
        keyName = "channels";
        harvestedData.at(keyName).get_to(channelsJson);

        // Fill DownloaderOpts JSON
        std::cout << "Finding the Downloader Data JSON file" << std::endl;
        keyName = "downloader";
        harvestedData.at(keyName).get_to(downloaderJson);

        // Archive Key-Value Pairs
        std::cout << "Loading Archive File Information" << std::endl;
        keyName = "archive";
        json archiveData = harvestedData.at(keyName);
        for(const auto &[key, value]: archiveData.items()){
            archiveData.at(key).get_to(archives[key]);
        }

        // Generator Key-Value Pairs
        std::cout << "Loading Generators File information" << std::endl;
        keyName = "generators";
        json generatorData = harvestedData.at(keyName);
        for(const auto &[key, value]: generatorData.items()){
            generatorData.at(key).get_to(generators[key]);
        }

    } catch (const std::exception &exception) {
        retStatus = JsonKeyValueNotFound;
        throw JsonKeyValueNotFoundException("The following key: " + keyName + " is Missing! in " + srcLocation);
    }

    // Match Archive - Generator Keys - can throw exception
    if(!matchArchivesAndGeneratorKeys()){
        retStatus = KeyPairsMismatch;
        throw KeyValuePairMismatchException(
                "Key Pairs Between Archives and Generators do not match in " + srcLocation
        );
    }

    retStatus = Success;
}

auto execDataOptions::matchArchivesAndGeneratorKeys() -> bool {
    std::cout << "\nNow matching Generator Keys with Archive's" << std::endl;
    std::unordered_set<std::string> hay;
    for (auto &[key, value]: archives) {
        hay.insert(key);
    }

    const bool stat = std::all_of(
            generators.begin(),
            generators.end(),
            [hay](const std::pair<const std::basic_string<char>, std::basic_string<char>>& key)
            {
                return hay.contains(key.first);
            }
    );
    std::cout << "Done Matching" << std::endl;
    return stat;
}

auto execDataOptions::getChannelsJson() const -> const std::string & {
    return channelsJson;
}

auto execDataOptions::getDownloaderJson() const -> const std::string & {
    return downloaderJson;
}

auto execDataOptions::getArchiveFileName(const std::string &key) -> const std::string & {
    return archives[key];
}

auto execDataOptions::getGeneratorFileName(const std::string &key) -> const std::string & {
    return generators[key];
}
