//
// Created by CagesThrottleUs on 10-06-2023.
//

#include "jsonKeyValueNotFoundException.hpp"

#include <utility>

auto JsonKeyValueNotFoundException::what() const noexcept -> const char * {
    return msg.c_str();
}

JsonKeyValueNotFoundException::JsonKeyValueNotFoundException(std::string msg) : msg(std::move(msg)) {}
