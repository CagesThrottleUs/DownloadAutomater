//
// Created by CagesThrottleUs on 23-06-2023.
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
 * @file configuration/dataPaths.cpp
 * @brief This file implements the functionality of configuration::DataPaths
 * @author Lakshya
 */

#include "dataPaths.hpp"

/**
 * @brief A default constructor to create object for configuration::DataPaths
 * @author Lakshya
 */
data::DataPaths::DataPaths() = default;

/**
 * @brief A getter function that returns the channel Path
 * @return a @c const std::string
 * @author Lakshya
 */
auto data::DataPaths::getChannels() const -> const std::string & {
    return channels;
}

/**
 * @brief A function that sets the channel path link
 * @details It is necessary to check before hand that the path actually exists
 * @param channels a string that tells the location of path
 * @author Lakshya
 */
void data::DataPaths::setChannels(const std::string &channels) {
    DataPaths::channels = channels;
}

/**
 * @brief A function that returns the path to downloader configuration
 * @return A @c const std::string
 * @author Lakshya
 */
auto data::DataPaths::getDownloader() const -> const std::string & {
    return downloader;
}

/**
 * @brief A function that sets the link to downloader configuration file.
 * @details It is necessary to check before hand that the path actually exists.
 * @param downloader The path where downloader configuration exist
 * @author Lakshya
 */
void data::DataPaths::setDownloader(const std::string &downloader) {
    DataPaths::downloader = downloader;
}

/**
 * @brief A function that returns the path to archiving links file
 * @return A @c const std::string&
 * @author Lakshya
 */
auto data::DataPaths::getLinksIdentifier() const -> const std::string & {
    return linksIdentifier;
}

/**
 * @brief A function that sets the path to archive links file
 * @details It is necessary to check before hand that the file actually exists
 * @param linksIdentifier the path to the archive links file
 * @author Lakshya
 */
void data::DataPaths::setLinksIdentifier(const std::string &linksIdentifier) {
    DataPaths::linksIdentifier = linksIdentifier;
}

/**
 * @brief A function that returns the path to archive names file
 * @return A @c const std::string
 * @author Lakshya
 */
auto data::DataPaths::getTitles() const -> const std::string & {
    return titles;
}

/**
 * @brief A function that sets the path to archive names file
 * @details It is necessary to check before hand that the file actually exists
 * @param titles The path to archive links
 * @author Lakshya
 */
void data::DataPaths::setTitles(const std::string &titles) {
    DataPaths::titles = titles;
}
