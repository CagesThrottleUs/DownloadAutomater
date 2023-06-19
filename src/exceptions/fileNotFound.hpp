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

#ifndef EXCEPTIONS_FILENOTFOUND_HPP
#define EXCEPTIONS_FILENOTFOUND_HPP

#include <exception>
#include <filesystem>
#include <string>

/**
 * @class FileNotFound fileNotFound.hpp "exceptions/fileNotFound.hpp"
 * @brief This is an exception class associated if a file exists or not.
 * @author Lakshya
 * @copyright MIT
 * @example To throw: @c throw FileNotFound(str)
 * @example To catch: @c catch(...){ std::cout << e.what() << std::endl; }
 * @implements @c std::exception
 */
class FileNotFound: virtual public std::exception{
    /**
     * @memberof FileNotFound
     * @brief string to hold the message associated with exeception
     * @type @c std::string
     */
    std::string msg;
public:
    explicit FileNotFound(std::string msg);
    [[nodiscard]] auto what() const noexcept -> const char * override;
    static auto checkIfFileExists(const std::string& srcFileLocation)  noexcept -> bool;
private:
    static auto createPath(const std::string &basicString) noexcept -> std::filesystem::path;
};


#endif //EXCEPTIONS_FILENOTFOUND_HPP
