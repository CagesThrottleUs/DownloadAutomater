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

/**
 * @file utils/miscFunctions.cpp
 * @brief This file defines the mainDriver functions in a namespace that can be used,
 * throughout the program. Declaration in @a utils/miscFunctions.hpp
 * @cite https://stackoverflow.com/q/10816600/13496837
 * @cite https://stackoverflow.com/q/1434937/13496837
 * @author Lakshya
 */

#include "../exceptions/jsonic.hpp"
#include "../exceptions/fileNotFound.hpp"
#include "constants.hpp"
#include "miscFunctions.hpp"
#include <iostream>

namespace mainDriver{
    /**
     * @brief This function was found during online search and it allows for more robust and reusable logging
     * @param msg A string that describes the message
     * @param location the <source_location> variable - no need to touch unless you know about source_location
     * @author Lakshya
     * @cite https://en.cppreference.com/w/cpp/utility/source_location/function_name
     * @cite https://en.cppreference.com/w/cpp/utility/source_location
     */
    void logUsingSourceLocation(
            const std::string& msg,
            const std::source_location location
    ) noexcept{
        std::clog   << "[debug] "
                    << "[from " << location.file_name() << "(" << location.line() << ":" << location.column() << ")]: "
                    << "In " << location.function_name() << " following message was received - " << std::endl;
        std::clog << msg << std::endl;
    }

    /**
     * @brief A sugar coat function to update ExitCode, throw FileNotFoundException Exception and add Debug logs
     * @details The user of function is expected to use the updated ExitCode value and stop the program directly! This
     * function internally uses FileNotFoundException::checkIfFileExists.
     * @throws FileNotFoundException
     * @param source A string that tells the path to location
     * @param code The ExitCode reference to be recorded with
     * @see ../exceptions/fileNotFound.hpp
     * @author Lakshya
     */
    void checkForFilesAndUpdateReturnStatus(const std::string& source, ExitCode &code){
        if(!FileNotFoundException::checkIfFileExists(source)){
            code = ExitCode::RETURN_FILE_NOT_FOUND;
            // Report Errors
            std::cout << "The file - " << source << " could not be found!" << std::endl;
            std::cout << "ABORTING!" << std::endl;

            std::string msg;
            mainDriver::appendMessagesForLog(msg,
                                             "Exception created - FileNotFoundException"
            );
            mainDriver::appendMessagesForLog(msg,
                                       "The source file - " + source
            );
            mainDriver::appendMessagesForLog(msg,
                                             "ExitCode updated - ExitCode::RETURN_FILE_NOT_FOUND"
            );
            mainDriver::logUsingSourceLocation(msg);

            throw FileNotFoundException("The FILE - " + source + " is not a valid PATH.");
        }
        code = ExitCode::RETURN_OK;
    }

    /**
     * @brief This function basically pads a tab and ends with a new line for the running messages.
     * @param runningMessage the string object to be manipulated
     * @param toAdd the message to add to @c runningMessage
     * @author Lakshya
     */
    void appendMessagesForLog(std::string& runningMessage, const std::string& toAdd) noexcept{
        runningMessage += "[debug]\t";
        runningMessage += toAdd;
        runningMessage += "\n";
    }

    /**
     * @brief The function will create a text that can be seen on Terminal that tells what must be done in case of
     * Erroneous execution.
     * @param code The ExitCode enumeration
     * @author Lakshya
     */
    void exitMessage(const ExitCode& code){
        if(code != ExitCode::RETURN_OK){
            std::cout << "The program ended with ERRORS - please provide " << constants::DEBUG_FILE
                      << " for testing!" << std::endl;
        }
    }
    /**
     * @brief A utility function that describes the ending message from the cases of try and catch blocks
     * @param err the @c std::exception
     * @param code the exitCode to be used
     * @return the integer converted value for exitCode marked as @c [[nodiscard]]
     */
    auto errorCodedEnding(const std::exception& err, const ExitCode& code) -> int{
        std::cout << err.what() << std::endl;
        mainDriver::exitMessage(code);
        return static_cast<int>(code);
    }

    /**
     * @brief This a reusable function that would parse files and provide a common ground for handling all related
     * exceptions.
     * @param file the file stream to read from
     * @param code the exitCode to be updated
     * @return a nlohmann::json object
     * @throws JsonicExceptions
     * @author Lakshya
     */
    auto parseJsonFile(std::ifstream& file, ExitCode& code) -> json{
        json data;
        try{
            data = json::parse(file);
        } catch(const json::parse_error& err){
            std::string msg;
            mainDriver::appendMessagesForLog(msg,
                                             "Exception Caught - JSON PARSING ERROR");
            mainDriver::appendMessagesForLog(msg,
                                             "Exception ID - " + std::to_string(err.id));
            mainDriver::appendMessagesForLog(msg,
                                             "Exact Reason - " + std::string(err.what()));
            mainDriver::appendMessagesForLog(msg,
                                             "BytePosition - " + std::to_string(err.byte));
            mainDriver::logUsingSourceLocation(msg);
            code = ExitCode::RETURN_JSON_PARSE_ERROR;
            throw JsonicExceptions("An unexpected JSON parsing error has occurred!");
        }
        return data;
    }

    /**
     * @brief This function allows you to access a json configuration from key and returns a json object for the same.
     * @param data A JSON object
     * @param key A string telling key
     * @param code the exitCode to update for errors
     * @return The json object accessed or default object
     * @throws JsonicExceptions
     * @author Lakshya
     */
    auto accessJsonByKey(const json& data, const std::string& key, ExitCode& code) -> json{
        json temp;
        try{
            temp = data.at(key);
        } catch (const json::out_of_range &err){
            std::string msg;
            mainDriver::appendMessagesForLog(msg,
                                             "Exception Caught - JSON Out of Range");
            mainDriver::appendMessagesForLog(msg,
                                             "Exception ID - " + std::to_string(err.id));
            mainDriver::appendMessagesForLog(msg,
                                             "Exact Reason - " + std::string(err.what()));
            mainDriver::logUsingSourceLocation(msg);
            code = ExitCode::RETURN_JSON_OUT_OF_RANGE_ERROR;
            throw JsonicExceptions("JSON Key - " + key + " was not found!");
        } catch (const json::type_error &err){
            std::string msg;
            mainDriver::appendMessagesForLog(msg,
                                             "Exception Caught - JSON Type Error");
            mainDriver::appendMessagesForLog(msg,
                                             "Exception ID - " + std::to_string(err.id));
            mainDriver::appendMessagesForLog(msg,
                                             "Exact Reason - " + std::string(err.what()));
            mainDriver::logUsingSourceLocation(msg);
            code = ExitCode::RETURN_JSON_TYPE_ERROR;
            throw JsonicExceptions("Expected a JSON object cannot perform at()!");
        }
        return temp;
    }
} // namespace mainDriver