//
// Created by CagesThrottleUs on 21-06-2023.
//

// MIT License
//
// Copyright (c) 2023-present Lakshya and other contributors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "handler.hpp"
#include "../exceptions/badUrlForm.hpp"
#include "../exceptions/directory.hpp"
#include "../exceptions/fileNotFound.hpp"
#include "../exceptions/jsonic.hpp"
#include "../external/json.hpp"
#include "../utils/constants.hpp"
#include "../utils/miscFunctions.hpp"
#include <fstream>
#include <thread>

using json = nlohmann::json;

/**
 * @brief A default constructor to create object for ConfigurationHandler
 */
ConfigurationHandler::ConfigurationHandler() = default;

/**
 * @brief The function that will do cleanup before destruction of the Configuration objects
 * @author Lakshya
 */
void ConfigurationHandler::stop() noexcept{
    ExitCode code = ExitCode::RETURN_OK;
    try{
        directories.deleteDirectories(code);
    } catch (const DirectoryExceptions& err) {
        std::string msg;
        mainDriver::appendMessagesForLog(msg,
                                         "Exception Caught - DirectoryExceptions");
        mainDriver::appendMessagesForLog(msg,
                                         "Exact Reason - " + std::string(err.what()));
        mainDriver::logUsingSourceLocation(msg);
    }
}

/**
 * @brief The function that will fill each of the configuration member of the Configuration Handler
 * @param configuration The reference to the CONFIG_FILE
 * @param code The stop Code marked for update
 * @throws JsonicExceptions
 * @author Lakshya
 * @cite https://stackoverflow.com/a/2512970/13496837
 * @cite https://en.cppreference.com/w/cpp/language/try_catch
 */
void ConfigurationHandler::fill(std::ifstream& configuration, ExitCode& code) {
    json data;
    json temp;
    data = mainDriver::parseJsonFile(configuration, code);

    // Filling Directories
    std::string keyName = "directories";
    std::vector<std::string> subkeyNames = {"root", "names"};
    temp = mainDriver::accessJsonByKey(data,constants::CONFIG_KEY_NAMES.at(keyName), code);
    directories.setRootLocation(
            mainDriver::accessJsonByKey(temp, subkeyNames[0], code).get<std::string>());
    directories.setNames(
            mainDriver::accessJsonByKey(temp, subkeyNames[1], code).get<std::vector<std::string>>());
    keyName = "";
    subkeyNames = {};

    // Filling Datapaths
    keyName = "dataPaths";
    subkeyNames = {"channels", "downloader", "linkIdentifier", "titles"};
    temp = mainDriver::accessJsonByKey(data, constants::CONFIG_KEY_NAMES.at(keyName), code);
    {
        std::string const localChannels =
                mainDriver::accessJsonByKey(temp, subkeyNames[0], code).get<std::string>();
        std::string const downloader =
                mainDriver::accessJsonByKey(temp, subkeyNames[1], code).get<std::string>();
        std::string const linkIdf =
                mainDriver::accessJsonByKey(temp, subkeyNames[2], code).get<std::string>();
        std::string const titles =
                mainDriver::accessJsonByKey(temp, subkeyNames[2], code).get<std::string>();
        bool const res = FileNotFoundException::checkIfFileExists(localChannels) &&
                         FileNotFoundException::checkIfFileExists(downloader) &&
                         FileNotFoundException::checkIfFileExists(linkIdf) &&
                         FileNotFoundException::checkIfFileExists(titles);
        if(!res){
            std::string msg;
            mainDriver::appendMessagesForLog(msg,
                                             "Exception Created - Trying to fill DataPaths");
            mainDriver::appendMessagesForLog(msg,
                                             "One of the following file is missing:");
            mainDriver::appendMessagesForLog(msg,
                                             localChannels);
            mainDriver::appendMessagesForLog(msg,
                                             downloader);
            mainDriver::appendMessagesForLog(msg,
                                             linkIdf);
            mainDriver::appendMessagesForLog(msg,
                                             titles);
            mainDriver::logUsingSourceLocation(msg);
            throw FileNotFoundException("One of the file does not exist - " +
                                        localChannels + ", " + downloader + ", " + linkIdf + ", " + titles);
        }
        paths.setChannels(localChannels);
        paths.setDownloader(downloader);
        paths.setLinksIdentifier(linkIdf);
        paths.setTitles(titles);
    }
    keyName = "";
    subkeyNames = {};

}

/**
 * @brief This function launches all the threads that will fill internal structure.
 * @details The function is guaranteed to throw no exceptions.
 * @details It will fill Trie for archives and Fill the downloader and channel information
 * @author Lakshya
 * @cite https://stackoverflow.com/q/65358028/13496837 - defining cpp arguments and reference
 * @cite https://stackoverflow.com/q/7798237/13496837 - passing this multiple times to a thread.
 */
void ConfigurationHandler::start() noexcept {
    std::thread createDirectory(
            &ConfigurationHandler::directoryCreationHandle,
            this
    );

    std::thread fillAndMixChannels(
            &ConfigurationHandler::channelsSetUpHandle,
            this
    );

    fillAndMixChannels.join();
    createDirectory.join();
}

/**
 * @brief A private member function that is responsibly creating directory without throwing exceptions. Intended for
 * threading use
 * @author Lakshya
 * @cite https://stackoverflow.com/q/329061/13496837
 */
void ConfigurationHandler::directoryCreationHandle() const noexcept {
    ExitCode code = ExitCode::RETURN_OK;
    try{
        directories.createDirectories(code);
    } catch (const DirectoryExceptions& err){
        std::string msg;
        mainDriver::appendMessagesForLog(msg,
                                         "Exception Caught - Directory Exception"
        );
        mainDriver::appendMessagesForLog(msg,
                                         "Could not create directories and thus updated stop code");
        mainDriver::appendMessagesForLog(msg,
                                         "Code - " + std::to_string(static_cast<int>(code)));
        mainDriver::logUsingSourceLocation(msg);
    }
}

/**
 * @brief In case user forgets to call stop() then call at the time of destruction
 * @author Lakshya
 */
ConfigurationHandler::~ConfigurationHandler() {
    stop();
}

/**
 * @brief A private member function of Configuration Handler that will gracefully fill the details of channels, without
 * creating any exceptions. Intended for multithreading.
 * @author Lakshya
 */
void ConfigurationHandler::channelsSetUpHandle() noexcept {
    ExitCode code = ExitCode::RETURN_OK;
    try{
        channels.fill(paths.getChannels(), code);
    } catch(const FileNotFoundException& err){
        std::string msg;
        mainDriver::appendMessagesForLog(msg,
                                         "Exception Caught - File Not Found!");
        mainDriver::appendMessagesForLog(msg,
                                         "Path - " + paths.getChannels());
        mainDriver::appendMessagesForLog(msg,
                                         "Exact Reason - " + std::string(err.what()));
        mainDriver::logUsingSourceLocation(msg);
    } catch (const JsonicExceptions& err){
        std::string msg;
        mainDriver::appendMessagesForLog(msg,
                                         "Exception Caught - JSON Error!");
        mainDriver::appendMessagesForLog(msg,
                                         "Exact Reason - " + std::string(err.what()));
        mainDriver::logUsingSourceLocation(msg);
    } catch (const BadURLFormException& err){
        std::string msg;
        mainDriver::appendMessagesForLog(msg,
                                         "Exception Caught - Malformed URL!");
        mainDriver::appendMessagesForLog(msg,
                                         "Exact Reason - " + std::string(err.what()));
        mainDriver::logUsingSourceLocation(msg);
    }
    channels.mix();
}

/**
 * @brief The constructor is generated explicitly because a non-default constructor is defined
 * @author Lakshya
 */
ConfigurationHandler::ConfigurationHandler(ConfigurationHandler &&) noexcept = default;

/**
 * @brief The constructor is generated explicitly because a non-default constructor is defined
 * @author Lakshya
 */
auto ConfigurationHandler::operator=(ConfigurationHandler &&)  noexcept -> ConfigurationHandler & = default;

/**
 * @brief The constructor is generated explicitly because a non-default constructor is defined
 * @author Lakshya
 */
auto ConfigurationHandler::operator=(const ConfigurationHandler &) -> ConfigurationHandler & = default;

/**
 * @brief The constructor is generated explicitly because a non-default constructor is defined
 * @author Lakshya
 */
ConfigurationHandler::ConfigurationHandler(const ConfigurationHandler &param) = default;
