//
// Created by lepag on 2/16/2025.
//

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Image.hpp"


namespace tri::util {
    Image::Image(const char *filePath) {
        unsigned char* pixels = stbi_load(filePath, &width, &height, &channels, STBI_rgb_alpha);
        if (pixels == nullptr) {
            throw std::runtime_error("Failed to load image");
        }

        GLFWimage icon;
        icon.width = width;
        icon.height = height;
        icon.pixels = pixels;

        data = pixels;
        image = icon;

        LOADED = true;
    }

    bool Image::loaded() const {
        return this->LOADED;
    }


    GLFWimage* Image::img() {
        return &this->image;
    }

    unsigned char* Image::pixels() const {
        return this->data;
    }

    void Image::free() {
        this->~Image();
    }

    Image::~Image() {
        if (this->loaded()) {
            stbi_image_free(this->data);
            this->data = nullptr;
        }
    }


} // util
// tri