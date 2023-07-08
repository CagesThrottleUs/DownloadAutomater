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

#ifndef DATA_DIRECTORIES_HPP
#define DATA_DIRECTORIES_HPP

/**
 * @brief internal namespace for Configuration that holds the different datatype composing CONFIG_FILE
 * @author Lakshya
 */
#include "../utils/exitCode.hpp"
#include <string>
#include <vector>

namespace data{
    /**
     * @class configuration::Directories
     * @brief The main goal of this class is to handle all calls and store the directories that will be directly
     * managed by the executable file.
     * @author Lakshya
     */
    class Directories{
        /**
         * @memberof configuration::Directories
         * @brief Tells the location of directory files from CONFIG_FILE
         * @details Both the relative and absolute location is allowed, but the major role for this allows user to
         * save their work in different folders as required
         * @author Lakshya
         */
        std::string rootLocation{"./"};
        /**
         * @memberof configuration::Directories
         * @brief The names of different directories that will be created and handled by executable.
         * @details all operations should implicitly add the rootLocation to the start.
         */
        std::vector<std::string> names{};
    public:
        Directories();
        [[nodiscard]] auto getRootLocation() const -> const std::string &;
        void setRootLocation(const std::string &location);
        [[nodiscard]] auto getNames() const -> const std::vector<std::string> &;
        void setNames(const std::vector<std::string> &listOfNames);
        void createDirectories(ExitCode &code) const;
        void deleteDirectories(ExitCode &code) const;
    };
} // namespace data
#endif //DATA_DIRECTORIES_HPP
