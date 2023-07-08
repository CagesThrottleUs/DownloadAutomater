//
// Created by CagesThrottleUs on 19-06-2023.
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

#include "configuration//handler.hpp"
#include "exceptions/fileNotFound.hpp"
#include "utils/constants.hpp"
#include "utils/exitCode.hpp"
#include "utils/miscFunctions.hpp"
#include <fstream>
#include <iostream>

auto main() -> int{
    /**
     * @brief The following two lines redirect std::clog
     * @cite https://bytes.com/topic/c/answers/136888-redirecting-cerr
     */
    std::ofstream out(constants::DEBUG_FILE, std::ios::trunc);
    auto *orig = std::clog.rdbuf(out.rdbuf());

    ExitCode code = ExitCode::RETURN_OK;

    // Check if file exists
    try {
        mainDriver::checkForFilesAndUpdateReturnStatus(constants::CONFIG_FILE, code);
    } catch (const FileNotFoundException &exception) {
        return mainDriver::errorCodedEnding(exception, code);
    }

    // Load configuration prep
    std::ifstream configInJson(constants::CONFIG_FILE);
    ConfigurationHandler configurationHandler;

    // Actually filling configuration
    try{
        configurationHandler.fill(configInJson, code);
    } catch(const std::exception& err){
        return mainDriver::errorCodedEnding(err, code);
    }
    //Unload all configuration
    configInJson.close();

    // Please note that when both start() and stop() are active
    // Then you will not see result during debug
    // Safely start all configuration structures
    configurationHandler.start();

    // Safely stop all Configuration properties
    configurationHandler.stop();

    // Put back the std::clog and close it
    std::clog.rdbuf(orig);
    out.close();

    mainDriver::exitMessage(code);
    return static_cast<int>(code);
}

/**
 * @todo Thread works - 1. fill Downloader Data structure using threads
*/