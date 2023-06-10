//
// Created by CagesThrottleUs on 09-06-2023.
//

#ifndef DOWNLOADAUTOMATER_KEYVALUEPAIRMISMATCHEXCEPTION_HPP
#define DOWNLOADAUTOMATER_KEYVALUEPAIRMISMATCHEXCEPTION_HPP


#include <exception>
#include <string>

class KeyValuePairMismatchException: virtual public std::exception{
    std::string msg;
public:
    explicit KeyValuePairMismatchException(std::string  _msg);
    [[nodiscard]] const char * what() const noexcept override;
};


#endif //DOWNLOADAUTOMATER_KEYVALUEPAIRMISMATCHEXCEPTION_HPP
