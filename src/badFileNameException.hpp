//
// Created by CagesThrottleUs on 09-06-2023.
//

#ifndef DOWNLOADAUTOMATER_BADFILENAMEEXCEPTION_HPP
#define DOWNLOADAUTOMATER_BADFILENAMEEXCEPTION_HPP


#include <exception>
#include <string>

class BadFileNameException : virtual public std::exception{
    std::string msg;
public:
    explicit BadFileNameException(std::string msg) noexcept;
    [[nodiscard]] auto what() const noexcept -> const char * override;
};


#endif //DOWNLOADAUTOMATER_BADFILENAMEEXCEPTION_HPP
