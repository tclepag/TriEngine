//
// Created by lepag on 2/16/2025.
//

#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <fstream>
#include <sstream>


namespace tri::util {

class File {
    public:
      static std::string fileToString(const char* path);
};

} // util
// tri

#endif //FILE_HPP
