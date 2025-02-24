//
// Created by TC on 2/21/2025.
//

#ifndef IMAGE_H
#define IMAGE_H

#include <GLFW/glfw3.h>
#include <string>

namespace tri::utility {

class Image {
public:
    struct ImageData {
        unsigned char* data;
        int width;
        int height;
        int channels;
    };
      explicit Image(const std::string& path);
      ~Image();

    [[nodiscard]] GLFWimage* GetGLFWimage() const;

    [[nodiscard]] ImageData GetImageData() const;

    void Free() const;
private:
    GLFWimage* m_image;

    int m_width;
    int m_height;
    int m_channels;
    unsigned char* m_data;
};

} // utility
// tri

#endif //IMAGE_H
