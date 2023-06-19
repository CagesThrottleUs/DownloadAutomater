//
// Created by CagesThrottleUs on 15-06-2023.
//

#include "playlist.hpp"
#include "badFileNameException.hpp"
#include "badUrlFormException.hpp"
#include "exitCode.hpp"
#include "json.hpp"
#include "jsonKeyValueNotFoundException.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void Playlist::fill(const std::string &srcLocation, int& retStatus) {
//    std::cout << "\nChecking if File exists Playlist::fill()" << std::endl;
    const std::filesystem::path path(srcLocation);
    if (!std::filesystem::exists(path)) {
        retStatus = BadFileName;
        throw BadFileNameException(path.string() + " NOT FOUND, please enter the correct name");
    }
//    std::cout << "FILE FOUND" << std::endl;

    std::ifstream myFile(srcLocation);
    json const data = json::parse(myFile);
    json temp;

    std::string keyName;

    try{
        keyName = "executionEngine";
        temp = data.at(keyName);

        keyName = "playlist";
        temp = temp.at(keyName);

        keyName = "execute?";
        temp.at(keyName).get_to(execute);

        keyName = "default";
        temp.at(keyName).get_to(defaultLink);

        keyName = "outputIn";
        temp.at(keyName).get_to(tempOutputFolder);

        keyName = "runSafeAfterFail";
        temp.at(keyName).get_to(safeMode);

        keyName = "outputMove";
        temp.at(keyName).get_to(finalMoveLocation);

        keyName = "shellLocation";
        temp.at(keyName).get_to(shellLocation);

        keyName = "shellName";
        temp.at(keyName).get_to(shellFileName);

        keyName = "shellNameSafe";
        temp.at(keyName).get_to(shellFileNameSafe);
    } catch (const std::exception &exception) {
        std::cout << exception.what() << std::endl;
        retStatus = JsonKeyValueNotFound;
        throw JsonKeyValueNotFoundException(
                "The expected key: " + keyName + " is missing in following JSON File! " + srcLocation
        );
    }

    if(!checkLinkFormation()){
        retStatus = BadURLForm;
        throw badURLFormException(
                "The URL filled: " + defaultLink + " does not conform to URL Standard. Please update!"
        );
    }
    myFile.close();

    retStatus = Success;
}

auto Playlist::checkLinkFormation() -> bool {
    return badURLFormException::CheckForURLForm(defaultLink);
}

void Playlist::download(Downloader &downloader, int &retStatus, Trie* trie) {
    const std::filesystem::path path(shellLocation);
    if(!std::filesystem::exists(path)){
        retStatus = BadFileName;
        throw BadFileNameException(path.string() + " NOT FOUND, please enter the correct name");
    }

    std::string const cmd = downloader.fullCommand();
    std::string const cmdSafe = downloader.fullCommandSafe();

    std::ofstream myFile;
    myFile.open(shellLocation + "/" + shellFileName);

    myFile << cmd << std::endl;
    myFile << "";

    try{
        trie->printTrie();
    } catch (const std::exception &exception) {
        std::cout << exception.what() << std::endl;
        retStatus = CFileErrors;
        return;
    }
    retStatus = Success;
}

auto Playlist::isExecute() const -> bool {
    return execute;
}

Playlist::Playlist() = default;

