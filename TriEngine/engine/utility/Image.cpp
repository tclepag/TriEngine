//
// Created by TC on 2/21/2025.
//

#include "Image.h"

#include <iostream>
#include <ostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace tri::utility
{
    Image::Image(const std::string& path) {
        m_width = 0;
        m_height = 0;
        m_channels = 0;
        m_data = nullptr;

        stbi_set_flip_vertically_on_load(true);

        const char* stringToPath = path.c_str();

        stbi_uc *pixels = stbi_load(stringToPath, &m_width, &m_height, &m_channels, STBI_rgb_alpha);
        if (!pixels) {
            std::cerr << "Failed to load image: " << path << std::endl;
            return;
        }

        m_image = new GLFWimage{
            m_width,
            m_height,
            pixels,
        };

        m_data = pixels;
    }

    Image::~Image() {
        stbi_image_free(m_image);
        delete m_image;
    }

    GLFWimage * Image::GetGLFWimage() const {
        return m_image;
    }

    Image::ImageData Image::GetImageData() const {
        ImageData imageData{};
        imageData.width = m_width;
        imageData.height = m_height;
        imageData.channels = m_channels;
        imageData.data = m_data;
        return imageData;
    }

    void Image::Free() const {
        delete this;
    }
} // utility
// tri