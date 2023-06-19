cmake_minimum_required(VERSION 3.26)
project(DownloadAutomater)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS -Wall)
set(CMAKE_CXX_FLAGS -Wextra)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(
        DownloadAutomater
        # ADD files from now
        src/main.cpp src/utils/exitCode.hpp src/external/json.hpp src/utils/constants.hpp src/exceptions/fileNotFound.cpp src/exceptions/fileNotFound.hpp)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY scripts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})