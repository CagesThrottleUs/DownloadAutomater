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

#ifndef UTILS_EXITCODE_HPP
#define UTILS_EXITCODE_HPP

/**
 * @brief Describes the exit codes for program
 * @author Lakshya
 * @details Among the various different exit code each of the code may have their
 * own description attached to their name and can be used along with exceptions.
 * @copyright MIT
 * @example ExitCode is declared as a scoped enumeration -
 *  @code
 *  ExitCode code = ExitCode::RETURN_OK; // This is an object based use
 *  int value = ExitCode::RETURN_OK // Get the value directly.
 */
enum class ExitCode{
    /**
     * @brief everything in execution was OK!
     */
    RETURN_OK,
    /**
     * @brief The intended file was not found, use with File Finding exception
     */
    RETURN_FILE_NOT_FOUND
};

#endif //UTILS_EXITCODE_HPP
