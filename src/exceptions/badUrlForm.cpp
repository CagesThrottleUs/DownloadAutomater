//
// Created by CagesThrottleUs on 27-06-2023.
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

#include "badUrlForm.hpp"
#include <regex>
#include <utility>

/**
 * @brief A constructor for the exception object
 * @param msg The message to be passed.
 * @details You can find the message using the what() function
 * @author Lakshya
 */
BadURLFormException::BadURLFormException(std::string msg) : msg(std::move(msg)) {}

/**
 * @brief The overloaded function from @c std::exception
 * @return A constant pointer to a character
 * @overload @c std::exception::what()
 */
auto BadURLFormException::what() const noexcept -> const char * {
    return msg.c_str();
}

/**
 * @brief The function tells if a URL is in a good form or not.
 * @param url The string passed as a constant reference to check.
 * @return True if the URL is in form else false
 * @author Lakshya
 * @cite Copied from https://gist.github.com/dperini/729294
 */
auto BadURLFormException::CheckForURLForm(const std::string &url) -> bool {
    std::string const munch;
    std::string const pattern = munch +
            "^" +
            // protocol identifier (optional)
            // short syntax // still required
            "(?:(?:(?:https?|ftp):)?\\/\\/)" +
            // user:pass BasicAuth (optional)
            "(?:\\S+(?::\\S*)?@)?" +
            "(?:" +
            // IP address exclusion
            // private & local networks
            "(?!(?:10|127)(?:\\.\\d{1,3}){3})" +
            R"((?!(?:169\.254|192\.168)(?:\.\d{1,3}){2}))" +
            R"((?!172\.(?:1[6-9]|2\d|3[0-1])(?:\.\d{1,3}){2}))" +
            // IP address dotted notation octets
            // excludes loopback network 0.0.0.0
            // excludes reserved space >= 224.0.0.0
            // excludes network & broadcast addresses
            // (first & last IP address of each class)
            R"((?:[1-9]\d?|1\d\d|2[01]\d|22[0-3]))" +
            R"((?:\.(?:1?\d{1,2}|2[0-4]\d|25[0-5])){2})" +
            R"((?:\.(?:[1-9]\d?|1\d\d|2[0-4]\d|25[0-4])))" +
            "|" +
            // host & domain names, may end with dot
            // can be replaced by a shortest alternative
            // (?![-_])(?:[-\\w\\u00a1-\\uffff]{0,63}[^-_]\\.)+
            "(?:" +
            "(?:" +
            "[a-z0-9\\u00a1-\\uffff]" +
            "[a-z0-9\\u00a1-\\uffff_-]{0,62}" +
            ")?" +
            R"([a-z0-9\u00a1-\uffff]\.)" +
            ")+" +
            // TLD identifier name, may end with dot
            R"((?:[a-z\u00a1-\uffff]{2,}\.?))" +
            ")" +
            // port number (optional)
            "(?::\\d{2,5})?" +
            // resource path (optional)
            "(?:[/?#]\\S*)?" +
            "$";
    std::regex const url_regex(pattern);
    return std::regex_match(url, url_regex);
}
