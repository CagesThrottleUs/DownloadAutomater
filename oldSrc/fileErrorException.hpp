//
// Created by CagesThrottleUs on 15-06-2023.
//

#ifndef DOWNLOADAUTOMATER_FILEERROREXCEPTION_HPP
#define DOWNLOADAUTOMATER_FILEERROREXCEPTION_HPP


#include <exception>
#include <string>

class FileErrorException: virtual public std::exception{
    std::string msg;
public:
    explicit FileErrorException(std::string msg);

    [[nodiscard]] auto what() const noexcept -> const char * override;
};


#endif //DOWNLOADAUTOMATER_FILEERROREXCEPTION_HPP
