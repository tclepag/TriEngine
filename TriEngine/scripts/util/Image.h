//
// Created by lepag on 2/16/2025.
//

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <stdexcept>
#include <iostream>

#include <windows.h>


namespace tri::util {

class Image {
public:
    struct ImageData {
        int width;
        int height;
        int channels;
        unsigned char* data;
    };
    enum ImageType {
        WINDOWS,
        STB
    };
    explicit Image(const char* filePath, ImageType type);
    ~Image();

    // Returns the HBITMAP
    HBITMAP* img();
    // Returns the pixel data
    [[nodiscard]] ImageData getData() const;
    // Frees the image data
    void free();
    // Returns if the image was loaded
    [[nodiscard]] bool loaded() const;
private:
    int width{}, height{}, channels{};
    HBITMAP image{};
    unsigned char* pixels{};
    ImageType img_type;
    bool LOADED = false;
};

} // util
// tri

#endif //IMAGE_HPP
