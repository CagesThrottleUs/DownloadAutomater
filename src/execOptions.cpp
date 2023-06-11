//
// Created by CagesThrottleUs on 09-06-2023.
//

#include "execOptions.hpp"
#include "badFileNameException.hpp"
#include "exitCode.hpp"
#include "json.hpp"
#include "jsonKeyValueNotFoundException.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;

void execOptions::fill(const std::string &srcLocation, int &retStatus) {
    std::cout << "Checking if File exists (execOptions) \n" << std::endl;
    const std::filesystem::path path(srcLocation);
    if(!std::filesystem::exists(path)){
        retStatus = BadFileName;
        throw BadFileNameException(path.string() + " NOT FOUND, please enter the correct name");
    }
    std::cout << "FILE FOUND" << std::endl;
    std::ifstream myFile(srcLocation);
    json data = json::parse(myFile);

    try{
        // Fill Directories data
        std::cout << "\nTrying to fill Directories data" << std::endl;
        data.at("directories").get_to(directories);
    } catch (const std::exception &exception) {
        std::cout << exception.what() << std::endl;
        retStatus = JsonKeyValueNotFound;
        throw JsonKeyValueNotFoundException(
                "The expected key: directories is missing in following JSON File! " + srcLocation
        );
    }

    // Fill Executable Data Options
    std::cout << "Trying to fill Data Options for configurations" << std::endl;
    json const execDataOptsHarvested = data.at("data");
    execDataOptions.fill(execDataOptsHarvested, retStatus, srcLocation);

    myFile.close();
}

auto execOptions::getChannelsPath() -> const std::string & {
    return execDataOptions.getChannelsJson();
}

auto execOptions::getDownloaderPath() -> const std::string & {
    return execDataOptions.getDownloaderJson();
}

auto execOptions::getArchiveLinkPath() -> const std::string & {
    return execDataOptions.getArchiveFileName("links");
}

auto execOptions::getArchiveNamePath() -> const std::string & {
    return execDataOptions.getArchiveFileName("names");
}

auto execOptions::getGeneratorNamePath() -> const std::string & {
    return execDataOptions.getGeneratorFileName("names");
}


execOptions::execOptions() = default;
