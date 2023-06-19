//
// Created by CagesThrottleUs on 15-06-2023.
//

#ifndef DOWNLOADAUTOMATER_BADURLFORMEXCEPTION_HPP
#define DOWNLOADAUTOMATER_BADURLFORMEXCEPTION_HPP


#include <exception>
#include <string>

class badURLFormException: virtual public std::exception {
    std::string msg;
public:
    explicit badURLFormException(std::string msg);
    [[nodiscard]] auto what() const noexcept -> const char * override;
    static auto CheckForURLForm(const std::string& url) -> bool;
};


#endif //DOWNLOADAUTOMATER_BADURLFORMEXCEPTION_HPP
