//
// Created by CagesThrottleUs on 09-06-2023.
//

#include "badFileNameException.hpp"
#include <utility>

badFileNameException::badFileNameException(std::string msg) noexcept : msg(std::move(msg)) {

}

auto badFileNameException::what() const noexcept -> const char * {
    return msg.c_str();
}
