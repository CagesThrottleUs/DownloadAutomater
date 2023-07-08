cmake_minimum_required(VERSION 3.26)
project(DownloadAutomater)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS -Wall)
set(CMAKE_CXX_FLAGS -Wextra)
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_FLAGS -fPIC)

add_executable(
        DownloadAutomater
        # ADD files from now
        src/main.cpp
        src/utils/exitCode.hpp
        src/external/json.hpp
        src/utils/constants.hpp
        src/exceptions/fileNotFound.cpp
        src/exceptions/fileNotFound.hpp
        src/utils/miscFunctions.cpp
        src/utils/miscFunctions.hpp
        src/configuration/handler.cpp
        src/configuration/handler.hpp
        src/exceptions/directory.cpp
        src/exceptions/directory.hpp
        src/configuration/directories.cpp
        src/configuration/directories.hpp
        src/exceptions/jsonic.cpp
        src/exceptions/jsonic.hpp
        src/configuration/dataPaths.cpp
        src/configuration/dataPaths.hpp
        src/structures/channels.cpp src/structures/channels.hpp src/exceptions/badUrlForm.cpp src/exceptions/badUrlForm.hpp)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY scripts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})