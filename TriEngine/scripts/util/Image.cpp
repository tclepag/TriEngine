//
// Created by lepag on 2/16/2025.
//

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Image.h"


namespace tri::util {
    Image::Image(const char *filePath, ImageType type) {
        stbi_set_flip_vertically_on_load(true);
        unsigned char* pixels = stbi_load(filePath, &width, &height, &channels, STBI_rgb_alpha);
        if (pixels == nullptr) {
            throw std::runtime_error("Failed to load image");
        }

        std::cout << "Image loaded successfully. Width: " << width << ", Height: " << height << ", Channels: " << channels << std::endl;

        for (int i = 0; i < width * height * channels; i += channels) {
            if (i < 100) {  // Print first few pixels for verification
                std::cout << "Pixel " << i / channels << ": "
                          << "R: " << (int)pixels[i] << ", "
                          << "G: " << (int)pixels[i + 1] << ", "
                          << "B: " << (int)pixels[i + 2];
                if (channels == 4) {
                    std::cout << ", A: " << (int)pixels[i + 3];
                }
                std::cout << std::endl;
            }
        }


        img_type = type;

        HBITMAP icon = nullptr;
        switch (type) {
            case WINDOWS: {
                BITMAPINFO bmi = {};
                bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
                bmi.bmiHeader.biWidth = width;
                bmi.bmiHeader.biHeight = -height;
                bmi.bmiHeader.biPlanes = 1;
                bmi.bmiHeader.biBitCount = 32;
                bmi.bmiHeader.biCompression = BI_RGB;

                void* bitmapData = nullptr;
                HBITMAP hBitmap = CreateDIBSection(nullptr, &bmi, DIB_RGB_COLORS, &bitmapData, nullptr, 0);
                if (hBitmap && bitmapData) {
                    memcpy(bitmapData, pixels, width * height * 4);
                }
                image = icon;
                stbi_image_free(pixels);
            }

            case STB: {
                this->pixels = pixels;
            }
        }

        LOADED = true;
    }

    bool Image::loaded() const {
        return this->LOADED;
    }

    Image::ImageData Image::getData() const {
        return {
            width,
            height,
            channels,
            pixels
        };
    }

    HBITMAP* Image::img() {
        return &this->image;
    }

    void Image::free() {
        delete this;
    }

    Image::~Image() {
        switch (img_type) {
            case WINDOWS:
                DeleteObject(image);
            case STB:
                stbi_image_free(pixels);
                pixels = nullptr;
        }
    }


} // util
// tri