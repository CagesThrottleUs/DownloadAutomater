//
// Created by CagesThrottleUs on 10-06-2023.
//

#include "jsonKeyValueNotFoundException.hpp"

#include <utility>

auto jsonKeyValueNotFoundException::what() const noexcept -> const char * {
    return msg.c_str();
}

jsonKeyValueNotFoundException::jsonKeyValueNotFoundException(std::string msg) : msg(std::move(msg)) {}
