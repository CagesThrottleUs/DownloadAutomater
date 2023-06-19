//
// Created by CagesThrottleUs on 15-06-2023.
//

#include "fileErrorException.hpp"
#include <utility>

auto FileErrorException::what() const noexcept -> const char * {
    return msg.c_str();
}

FileErrorException::FileErrorException(std::string msg) : msg(std::move(msg)) {}
