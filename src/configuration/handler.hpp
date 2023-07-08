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
 * @file configuration/configurationHandler.hpp
 * @brief This file contains the classes definition for configuration handling from the configuration file
 * @author Lakshya
 */

#ifndef CONFIGURATION_HANDLER_HPP
#define CONFIGURATION_HANDLER_HPP

#include "../utils/exitCode.hpp"
#include "../structures/channels.hpp"
#include "dataPaths.hpp"
#include "directories.hpp"
#include <string>
#include <vector>

/**
 * @brief The Class that handles all the options for CONFIG_FILE
 * @details THE OBJECT MUST CALL stop() before deletion
 * @note THE OBJECT MUST CALL stop() before deletion
 * @author Lakshya
 */
class ConfigurationHandler {
    /**
     * @brief This member will hold the information about the directories under management of this class.
     */
    data::Directories directories;

    /**
     * @brief this member will hold the information about different data sources for the application.
     */
    data::DataPaths paths;

    /**
     * @brief This member will hold the mature channels archive points.
     */
     data::Channels channels;
public:
    ConfigurationHandler();
    ConfigurationHandler(const ConfigurationHandler&);
    ConfigurationHandler(ConfigurationHandler&&) noexcept ;
    auto operator=(const ConfigurationHandler&) -> ConfigurationHandler&;
    auto operator=(ConfigurationHandler&&)  noexcept -> ConfigurationHandler&;
    void stop() noexcept;
    void fill(std::ifstream& configuration, ExitCode& code);
    void start() noexcept;
    virtual ~ConfigurationHandler();
private:
    void directoryCreationHandle() const noexcept;
    void channelsSetUpHandle() noexcept;
};


#endif //CONFIGURATION_HANDLER_HPP
