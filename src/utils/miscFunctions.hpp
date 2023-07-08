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
 * @file utils/miscFunctions.hpp
 * @brief This file declares the mainDriver functions in a namespace that can be used,
 * throughout the program.
 * @cite https://stackoverflow.com/q/10816600/13496837
 * @cite https://stackoverflow.com/q/1434937/13496837
 * @author Lakshya
 */

#ifndef UTILS_MISCFUNCTIONS_HPP
#define UTILS_MISCFUNCTIONS_HPP

#include "exitCode.hpp"
#include "../external/json.hpp"
#include <source_location>
#include <string>

using json = nlohmann::json;

namespace mainDriver{
    void checkForFilesAndUpdateReturnStatus(const std::string& source, ExitCode &code);
    void logUsingSourceLocation(
            const std::string& msg,
            std::source_location location = std::source_location::current()
    ) noexcept;
    void appendMessagesForLog(std::string& runningMessage, const std::string& toAdd) noexcept;
    void exitMessage(const ExitCode& code);
    [[nodiscard]] auto errorCodedEnding(const std::exception& err, const ExitCode& code) -> int;
    [[nodiscard]] auto parseJsonFile(std::ifstream& file, ExitCode& code) -> json;
    [[nodiscard]] auto accessJsonByKey(const json& data, const std::string& key, ExitCode& code) -> json;
} // namespace mainDriver

#endif //UTILS_MISCFUNCTIONS_HPP
