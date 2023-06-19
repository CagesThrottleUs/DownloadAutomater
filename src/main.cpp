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

#include "utils/exitCode.hpp"
#include "utils/constants.hpp"
#include <fstream>
#include <iostream>

auto main() -> int{
    /**
     * @brief The following two lines redirect std::clog
     * @cite https://bytes.com/topic/c/answers/136888-redirecting-cerr
     */
    std::ofstream out(constants::DEBUG_FILE, std::ios::trunc);
    auto *orig = std::clog.rdbuf(out.rdbuf());

    ExitCode code = ExitCode::RETURN_OK;
    code = ExitCode::RETURN_FILE_NOT_FOUND;

    // Put back the std::clog and close it
    std::clog.rdbuf(orig);
    out.close();
    return static_cast<int>(code);
}