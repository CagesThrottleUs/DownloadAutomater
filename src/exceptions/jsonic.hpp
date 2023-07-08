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

#ifndef EXCEPTIONS_JSONIC_HPP
#define EXCEPTIONS_JSONIC_HPP

#include <exception>
#include <string>

/**
 * @class JsonicExceptions
 * @brief This is an exception class associated with all nlohmann::json Exceptions
 * @author Lakshya
 * @implements @c std::exception
 */
class JsonicExceptions: virtual public std::exception {
    /**
     * @memberof JsonicExceptions
     * @brief string to hold the message associated with exception
     * @type @c std::string
     */
    std::string msg;
public:
    explicit JsonicExceptions(std::string msg);
    [[nodiscard]] auto what() const noexcept -> const char * override;
};


#endif //EXCEPTIONS_JSONIC_HPP
