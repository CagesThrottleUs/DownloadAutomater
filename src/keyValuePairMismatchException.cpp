//
// Created by CagesThrottleUs on 09-06-2023.
//

#include "keyValuePairMismatchException.hpp"

#include <utility>

KeyValuePairMismatchException::KeyValuePairMismatchException(std::string _msg): msg(std::move(_msg)) {

}

auto KeyValuePairMismatchException::what() const noexcept -> const char * {
    return msg.c_str();
}
