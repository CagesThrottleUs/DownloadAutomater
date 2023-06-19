//
// Created by CagesThrottleUs on 19-06-2023.
//

// MIT License
//
// Copyright (c) 2023-present Lakshya and other contributors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

/**
 * @file exceptions/fileNotFound.cpp
 * @brief This file is the implementation file for the various different classes
 * that are present in the declaration @a exceptions/fileNotFound.hpp
 * @author Lakshya
 */

#include "fileNotFound.hpp"
#include <filesystem>
#include <iostream>
#include <utility>

/**
 * @brief Copies and moves the message for the class
 * @author Lakshya
 * @param msg The message to be copied
 * @details Originally the constructor was supposed to just get the constant reference,
 * and copy and paste that to PRIVATE:msg but clang-tidy tells me to use std::move with copy
 */
FileNotFound::FileNotFound(std::string msg) : msg(std::move(msg)) {}

/**
 * @brief Tells the What the exception really was
 * @author Lakshya
 * @overload This overloads the std::exception's what
 * @details The function will directly return from the std::string::c_str() functions,
 * which is responsible for creating a constant pointer
 * @return a pointer to a constant data from the message in string.
 * @example @c std::cout << exception.what() << std::endl;
 */
auto FileNotFound::what() const noexcept -> const char * {
    return msg.c_str();
}

/**
 * @brief A static function to check if a file exists
 * @author Lakshya
 * @details This function internally uses std::filesystem. There are several exceptions may occur,
 * these are directly handled by this function and ensures that noexcept is followed. Possible
 * exceptions include
 * @c filesystem::filesystem_error
 * for OS API errors and
 * @c std::bad_alloc
 * if memory allocation fails.
 * @cite https://en.cppreference.com/w/cpp/filesystem/exists
 * @cite https://en.cppreference.com/w/cpp/filesystem/path/path
 * @cite https://en.cppreference.com/w/cpp/filesystem/filesystem_error
 * @param srcFileLocation A string to source file location
 * @return boolean value that tells whether a file exists or not
 */
auto FileNotFound::checkIfFileExists(const std::string &srcFileLocation) noexcept -> bool {
    try{
        const std::filesystem::path path = createPath(srcFileLocation);
        return std::filesystem::exists(path);
    } catch (const std::filesystem::filesystem_error& err){
        std::clog << "[debug] In FileNotFound::checkIfFileExists() from exceptions/fileNotFound.cpp" << std::endl;
        std::clog << "[debug] \t A FileSystem Error has occurred because of OS API Error" << std::endl;
        std::clog << "[debug] \t Exact Reason - what(): " << err.what() << std::endl;
        std::clog << "[debug] \t Exact Reason - path1(): " << err.path1() << std::endl;
        std::clog << "[debug] \t Exact Reason - code().value(): " << err.code().value() << std::endl;
        std::clog << "[debug] \t Exact Reason - code().message(): " << err.code().message() << std::endl;
        std::clog << "[debug] \t Exact Reason - code().category(): " << err.code().category().name() << std::endl;
    }
    return false;
}

/**
 * @brief creates a path variable to be copied
 * @author Lakshya
 * @details this function is necessary in itself because we want to make sure that no exceptions
 * are created. This member is created static private because we want to use this in checkIfFileExists().
 * @cite https://en.cppreference.com/w/cpp/filesystem/exists
 * @cite https://en.cppreference.com/w/cpp/memory/new/bad_alloc
 * @cite https://en.cppreference.com/w/cpp/filesystem/path/path
 * @param basicString
 * @c std::string
 * object
 * @return an
 * @c std::filesystem::path
 * object
 */
auto FileNotFound::createPath(const std::string &basicString) noexcept -> std::filesystem::path {
    try{
        std::filesystem::path path(basicString);
        return path;
    } catch (const std::exception& exception){
        std::clog << "[debug] In createPath() from exceptions/fileNotFound.cpp" << std::endl;
        std::clog << "[debug] \t An implementation defined exception has occurred!" << std::endl;
        std::clog << "[debug] \t Exact reason - what(): " << exception.what() << std::endl;
    }
    return {"./ThisPath {} $ $$$ DEFINITELY DOES NOT EXIST"};
}
