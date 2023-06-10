//
// Created by CagesThrottleUs on 09-06-2023.
//

#include "keyValuePairMismatchException.hpp"

#include <utility>

KeyValuePairMismatchException::KeyValuePairMismatchException(std::string _msg): msg(std::move(_msg)) {

}

const char *KeyValuePairMismatchException::what() const noexcept {
    return msg.c_str();
}
