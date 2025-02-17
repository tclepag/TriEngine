//
// Created by lepag on 2/16/2025.
//

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <stdexcept>
#include <iostream>
#include <GLFW/glfw3.h>


namespace tri::util {

class Image {
public:
    explicit Image(const char* filePath);
    ~Image();

    // Returns the stb image pixels
    unsigned char* pixels() const;
    // Returns the GLFWimage
    GLFWimage* img();
    // Frees the image data
    void free();
    // Returns if the image was loaded
    bool loaded() const;
private:
    int width{}, height{}, channels{};
    unsigned char* data;
    GLFWimage image{};
    bool LOADED = false;
};

} // util
// tri

#endif //IMAGE_HPP
