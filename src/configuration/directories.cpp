//
// Created by CagesThrottleUs on 22-06-2023.
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

#include "directories.hpp"
#include "../exceptions/directory.hpp"
#include "../exceptions/fileNotFound.hpp"
#include "../utils/miscFunctions.hpp"
#include <filesystem>

/**
 * @brief Default constructor to create object for Directories
 * @author Lakshya
 */
data::Directories::Directories() = default;

/**
 * @brief Default getter for the root location of the directories folder put together
 * @return Returns the string that tells the root location [[nodiscard]]
 * @author Lakshya
 */
auto data::Directories::getRootLocation() const -> const std::string & {
    return rootLocation;
}

/**
 * @brief Setter to redefine the root location for different directories
 * @param location A string to tell where the root Location is - can be absolute or relative
 * @author Lakshya
 */
void data::Directories::setRootLocation(const std::string &location) {
    Directories::rootLocation = location;
}

/**
 * @brief A getter for the different directory names
 * @return A vector of names of the directories managed.
 * @author Lakshya
 */
auto data::Directories::getNames() const -> const std::vector<std::string> & {
    return names;
}

/**
 * @brief Change the complete directory name list
 * @param listOfNames A vector of strings for different names
 * @author Lakshya
 */
void data::Directories::setNames(const std::vector<std::string> &listOfNames) {
    Directories::names = listOfNames;
}

/**
 * @brief The function generates all the Directories given in names
 * @details This function will use a lot of OS API call because it internally uses @c std::filesystem::create_directory
 * because of which this function is I/O intensive. Any contribution to make it safer and faster is appreciated.
 * @details The updated exit code must be directly used to stop the program safely.
 * @param code The ExitCode variable that marks changes
 * @throws DirectoryExceptions
 * @author Lakshya
 */
void data::Directories::createDirectories(ExitCode &code) const {
    std::string fullDirectoryName;
    std::filesystem::path path;
    std::string msg;
    std::vector<std::string> directoriesFailed;
    for(const auto& directory: getNames()){
        msg = "";
        fullDirectoryName = getRootLocation() + directory;
        path = FileNotFoundException::createPath(fullDirectoryName);
        bool isCreated = false;
        try{
            isCreated = std::filesystem::create_directory(path);
        } catch (std::filesystem::filesystem_error& err){
            mainDriver::appendMessagesForLog(msg,
                                             "Exception caught - "
                                             "filesystem_error has occurred because of OS API Error"
            );
            mainDriver::appendMessagesForLog(msg,
                                             "Exact Reason - what(): " + std::string(err.what())
            );
            mainDriver::appendMessagesForLog(msg,
                                             "Exact Reason - path1(): " + err.path1().string()
            );
            mainDriver::appendMessagesForLog(msg,
                                             "Exact Reason - code().value(): " +
                                             std::to_string(err.code().value())
            );
            mainDriver::appendMessagesForLog(msg,
                                             "Exact Reason - code().message(): " + err.code().message()
            );
            mainDriver::appendMessagesForLog(msg,
                                             "Exact Reason - code().category(): "
                                             + std::string(err.code().category().name())
            );
            mainDriver::logUsingSourceLocation(msg);
            isCreated = false;
            msg = "";
        }

        if(!isCreated){
            msg = "";
            directoriesFailed.push_back(fullDirectoryName);
            mainDriver::appendMessagesForLog(msg,
                                             "Exception created - Directory Creation"
            );
            mainDriver::appendMessagesForLog(msg,
                                             "Exception argument - " + fullDirectoryName
            );
            mainDriver::logUsingSourceLocation(msg);
        }
    }

    if(!directoriesFailed.empty()){
        fullDirectoryName = "";
        for(const auto& failed: directoriesFailed){
            fullDirectoryName += failed + ", ";
        }
        code = ExitCode::RETURN_FAILED_DIRECTORY_CREATION;
        throw DirectoryExceptions("The Directory was not created for - " + fullDirectoryName);
    }
    code = ExitCode::RETURN_OK;
}

/**
 * @brief The function delete all the Directories given in names
 * @details This function will use a lot of OS API call because it internally uses @c std::filesystem::create_directory
 * because of which this function is I/O intensive. Any contribution to make it safer and faster is appreciated.
 * @details The updated exit code must be directly used to stop the program safely.
 * @param code The ExitCode variable that marks changes
 * @throws DirectoryExceptions
 * @author Lakshya
 */
void data::Directories::deleteDirectories(ExitCode &code) const {
    std::string fullDirectoryName;
    std::filesystem::path path;
    std::string msg;
    std::vector<std::string> directoriesFailed;
    for(const auto& directory: getNames()){
        msg = "";
        fullDirectoryName = getRootLocation() + directory;
        path = FileNotFoundException::createPath(fullDirectoryName);
        std::uintmax_t totalDeleted = 0;
        try{
            totalDeleted = std::filesystem::remove_all(path);
        } catch (std::filesystem::filesystem_error& err){
            mainDriver::appendMessagesForLog(msg,
                                             "Exception caught - "
                                             "filesystem_error has occurred because of OS API Error"
            );
            mainDriver::appendMessagesForLog(msg,
                                             "Exact Reason - what(): " + std::string(err.what())
            );
            mainDriver::appendMessagesForLog(msg,
                                             "Exact Reason - path1(): " + err.path1().string()
            );
            mainDriver::appendMessagesForLog(msg,
                                             "Exact Reason - code().value(): " +
                                             std::to_string(err.code().value())
            );
            mainDriver::appendMessagesForLog(msg,
                                             "Exact Reason - code().message(): " + err.code().message()
            );
            mainDriver::appendMessagesForLog(msg,
                                             "Exact Reason - code().category(): "
                                             + std::string(err.code().category().name())
            );
            mainDriver::logUsingSourceLocation(msg);
            totalDeleted = 0;
            msg = "";
        }

        if(totalDeleted <= 0){
            directoriesFailed.push_back(fullDirectoryName);
            msg = "";

            mainDriver::appendMessagesForLog(msg,
                                             "Exception created - Directory Deletion"
            );
            mainDriver::appendMessagesForLog(msg,
                                             "Exception argument - " + fullDirectoryName
            );
            mainDriver::logUsingSourceLocation(msg);


        }

    }
    if(!directoriesFailed.empty()){
        fullDirectoryName = "";
        for(const auto& failed: directoriesFailed){
            fullDirectoryName += failed + ", ";
        }
        code = ExitCode::RETURN_FAILED_DIRECTORY_DELETION;
        throw DirectoryExceptions("The Directory was not deleted for - " + fullDirectoryName);
    }
    code = ExitCode::RETURN_OK;
}