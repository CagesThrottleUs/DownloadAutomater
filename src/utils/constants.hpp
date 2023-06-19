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

/**
 * @file utils/constants.hpp
 * @brief This file is the program and constant data values used in program.
 */
#ifndef UTILS_CONSTANTS_HPP
#define UTILS_CONSTANTS_HPP

#include <fstream>
#include <string>

/**
 * @brief defines all the program constants to be used
 * @author Lakshya
 * @copyright MIT
 * @headerfile "utils/constants.hpp"
 * @cite https://stackoverflow.com/a/2268826/13496837
 * @example Get access to the values after including the header file with
 * constants namespace use as @c constants::CONFIG_FILE
 */
namespace constants{
    /**
     * @brief the file that will be accessed to fill all the executable centric data.
     */
    const std::string CONFIG_FILE = "./data/executable.opts.json";
    const std::string DEBUG_FILE = "./debug.txt";
} // namespace constants

#endif //UTILS_CONSTANTS_HPP
