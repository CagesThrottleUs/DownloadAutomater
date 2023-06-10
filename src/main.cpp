#include "execOptions.hpp"
#include "exitCode.hpp"
#include <iostream>

auto main() -> int {
    int returnStatus = Success;
    execOptions dataAndDirectoryOptions;

    // Filling Configuration file
    try{
        // Filling the executable options
        std::cout << "The Program is right now trying to fill the executable options" << std::endl;
        dataAndDirectoryOptions.fill("./data/executable.opts.json", returnStatus);
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
        return returnStatus;
    }
    return Success;
}
