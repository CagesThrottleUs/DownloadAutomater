//
// Created by CagesThrottleUs on 15-06-2023.
//

#include "badUrlFormException.hpp"
#include <utility>
#include <iostream>
#include <regex>

badURLFormException::badURLFormException(std::string msg) : msg(std::move(msg)) {}

auto badURLFormException::what() const noexcept -> const char * {
    return msg.c_str();
}

auto badURLFormException::CheckForURLForm(const std::string &url) -> bool {
    // Taken from https://gist.github.com/dperini/729294
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
