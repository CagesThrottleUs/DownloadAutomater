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
 * @file configuration/dataPaths.hpp
 * @brief This file describes the simple locations for the different paths of configuration from which we will
 * fill the other configuration formats
 * @author Lakshya
 */

#ifndef CONFIGURATION_DATAPATHS_HPP
#define CONFIGURATION_DATAPATHS_HPP

#include <string>

namespace data {

    class DataPaths {
        std::string channels;
        std::string downloader;
        std::string linksIdentifier;
        std::string titles;
    public:
        DataPaths();
        [[nodiscard]] auto getChannels() const -> const std::string &;
        void setChannels(const std::string &channels);
        [[nodiscard]] auto getDownloader() const -> const std::string &;
        void setDownloader(const std::string &downloader);
        [[nodiscard]] auto getLinksIdentifier() const -> const std::string &;
        void setLinksIdentifier(const std::string &linksIdentifier);
        [[nodiscard]] auto getTitles() const -> const std::string &;
        void setTitles(const std::string &titles);
    };

} // namespace data

#endif //CONFIGURATION_DATAPATHS_HPP
