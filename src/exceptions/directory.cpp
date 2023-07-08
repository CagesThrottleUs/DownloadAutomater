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

#include "directory.hpp"
#include <utility>

/**
 * @brief Copies and moves the message for the class
 * @author Lakshya
 * @param msg The message to be copied
 */
DirectoryExceptions::DirectoryExceptions(std::string msg) : msg(std::move(msg)) {}

/**
 * @brief Tells the What the exception really was
 * @author Lakshya
 * @overload This overloads the std::exception's what
 * @details The function will directly return from the std::string::c_str() functions,
 * which is responsible for creating a constant pointer
 * @return a pointer to a constant configuration from the message in string.
 * @example @c std::cout << exception.what() << std::endl;
 */
auto DirectoryExceptions::what() const noexcept -> const char * {
    return msg.c_str();
}
