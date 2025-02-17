//
// Created by lepag on 2/16/2025.
//

#include "File.hpp"

#include <iostream>


namespace tri::util {
    std::string File::fileToString(const char* path) {
        std::ifstream file(path);
        if (!file || !file.is_open()) {
            std::cerr << "Error opening file " << path << std::endl;
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
} // util
// tri