//
// Created by CagesThrottleUs on 09-06-2023.
//

#include "badFileNameException.hpp"
#include <utility>

BadFileNameException::BadFileNameException(std::string msg) noexcept : msg(std::move(msg)) {

}

auto BadFileNameException::what() const noexcept -> const char * {
    return msg.c_str();
}
