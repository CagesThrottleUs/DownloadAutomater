//
// Created by CagesThrottleUs on 10-06-2023.
//

#ifndef DOWNLOADAUTOMATER_JSONKEYVALUENOTFOUNDEXCEPTION_HPP
#define DOWNLOADAUTOMATER_JSONKEYVALUENOTFOUNDEXCEPTION_HPP

#include <exception>
#include <string>

class JsonKeyValueNotFoundException : virtual public std::exception{
    std::string msg;
public:
    explicit JsonKeyValueNotFoundException(std::string msg);
    [[nodiscard]] auto what() const noexcept -> const char * override;
};


#endif //DOWNLOADAUTOMATER_JSONKEYVALUENOTFOUNDEXCEPTION_HPP