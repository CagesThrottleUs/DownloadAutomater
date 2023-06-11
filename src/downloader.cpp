//
// Created by CagesThrottleUs on 11-06-2023.
//

#include "downloader.hpp"
#include "badFileNameException.hpp"
#include "exitCode.hpp"
#include "json.hpp"
#include "jsonKeyValueNotFoundException.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>

using json = nlohmann::json;

iml::DownloaderArgs::DownloaderArgs(
        std::string option,
        std::string value,
        bool includeOnFail
) :
    option(std::move(option)),
    value(std::move(value)),
    includeOnFail(includeOnFail)
{

}

auto iml::DownloaderArgs::getOption() const -> const std::string & {
    return option;
}

void iml::DownloaderArgs::setOption(const std::string &option) {
    DownloaderArgs::option = option;
}

auto iml::DownloaderArgs::getValue() const -> const std::string & {
    return value;
}

void iml::DownloaderArgs::setValue(const std::string &value) {
    DownloaderArgs::value = value;
}

auto iml::DownloaderArgs::isIncludeOnFail() const -> bool {
    return includeOnFail;
}

void iml::DownloaderArgs::setIncludeOnFail(bool includeOnFail) {
    DownloaderArgs::includeOnFail = includeOnFail;
}

auto iml::DownloaderArgs::command() const -> std::string {
    std::string cmd;
    cmd += getOption() + " ";
    if(!getValue().empty()){
        cmd += "\"" + getValue() + "\"";
    }
    return cmd;
}

iml::DownloaderArgs::DownloaderArgs() = default;

Downloader::Downloader() = default;

void Downloader::fill(const std::string &path, int &retStatus) {
    std::cout << "\nThe program right now is trying to fill Downloader Arguments" << std::endl;
    const std::filesystem::path dataPath(path);
    if(!std::filesystem::exists(dataPath)){
        retStatus = BadFileName;
        throw BadFileNameException(dataPath.string() + " was NOT FOUND, please enter the correct name!");
    }

    // Start filling data with json
    std::ifstream myFile(path);
    json const data = json::parse(myFile);

    std::string keyName;

    try{
        // Get the executable path
        keyName = "executable";
        data.at(keyName).get_to(executablePath);

        // Fill the options data
        keyName = "options";
        json optionList = data.at(keyName);
        for(const auto& ele: optionList){
            keyName = "option";
            std::string opt;
            ele.at(keyName).get_to(opt);
            keyName = "value";
            std::string val;
            ele.at(keyName).get_to(val);
            keyName = "includeInCaseOfFail";
            bool inc = false;
            ele.at(keyName).get_to(inc);
            iml::DownloaderArgs const temp(opt, val, inc);
            arguments.push_back(temp);
        }

        // Fill Bad options failure
        keyName = "BadOptionsFailure";
        json const& badOpts = data.at(keyName);
        keyName = "options";
        optionList = badOpts.at(keyName);
        for(const auto& ele: optionList){
            keyName = "option";
            std::string opt;
            ele.at(keyName).get_to(opt);
            keyName = "value";
            std::string val;
            ele.at(keyName).get_to(val);
            keyName = "includeInCaseOfFail";
            bool inc = false;
            ele.at(keyName).get_to(inc);
            iml::DownloaderArgs const temp(opt, val, inc);
            badOptions.push_back(temp);
        }

        // Fill Frequency matcher option
        keyName = "freqMatcher";
        optionList = data.at(keyName);
        keyName = "option";
        std::string opt;
        optionList.at(keyName).get_to(opt);
        keyName = "value";
        std::string val;
        optionList.at(keyName).get_to(val);
        keyName = "includeInCaseOfFail";
        bool inc = false;
        optionList.at(keyName).get_to(inc);
        freqMatcher.setOption(opt);
        freqMatcher.setValue(val);
        freqMatcher.setIncludeOnFail(inc);
    } catch (const std::exception &exception) {
        std::cout << exception.what() << std::endl;
        retStatus = JsonKeyValueNotFound;
        throw JsonKeyValueNotFoundException(
                "The expected key: " + keyName + " is missing in following JSON File! " + path
        );
    }
    myFile.close();
}

/**
 * @brief Does provide a padded space at the end
 */
auto Downloader::fullCommand() -> std::string {
    std::string cmd;
    cmd += executablePath + " ";

    for(auto& ele: arguments){
        cmd += ele.command() + " ";
    }

    return cmd;
}

auto Downloader::fullCommandWithFreqMatcher() -> std::string {
    return fullCommand() + freqMatcher.command() + " ";
}

/**
 * @brief Does provide a padded space at the end
 */
auto Downloader::fullCommandSafe() -> std::string {
    std::string cmd;
    cmd += executablePath + " ";

    for(auto& ele: arguments){
        if(ele.isIncludeOnFail()){
            cmd += ele.command() + " ";
        }
    }

    for(auto& ele: badOptions){
        if(ele.isIncludeOnFail()){
            cmd += ele.command() + " ";
        }
    }

    return cmd;
}

auto Downloader::fullCommandSafeWithFreqMatcher() -> std::string {
    return fullCommandSafe() + (freqMatcher.isIncludeOnFail() ? freqMatcher.command() : "");
}
