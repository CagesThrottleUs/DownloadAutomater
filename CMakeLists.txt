cmake_minimum_required(VERSION 3.26)
project(DownloadAutomater)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS -Wall)
set(CMAKE_CXX_FLAGS -Wextra)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(
        DownloadAutomater
        src/main.cpp
        src/json.hpp
        src/execOptions.cpp
        src/execOptions.hpp
        src/badFileNameException.cpp
        src/badFileNameException.hpp
        src/execDataOptions.cpp
        src/execDataOptions.hpp
        src/exitCode.hpp
        src/keyValuePairMismatchException.cpp
        src/keyValuePairMismatchException.hpp
        src/jsonKeyValueNotFoundException.cpp
        src/jsonKeyValueNotFoundException.hpp
        src/channels.cpp
        src/channels.hpp
        src/threadUtilities.cpp src/threadUtilities.hpp src/downloader.cpp src/downloader.hpp src/trie.cpp src/trie.hpp)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY scripts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})