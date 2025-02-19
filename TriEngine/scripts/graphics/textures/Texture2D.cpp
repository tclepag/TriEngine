//
// Created by lepag on 2/18/2025.
//

#include "Texture2D.h"



namespace tri::graphics::textures {
    Texture2D::Texture2D(util::Image* image, const TX2D& info) : BaseTextureClass() {
        util::Image::ImageData data = image->getData();
        target = GL_TEXTURE_2D;
        glGenTextures(1, &texture);
        glBindTexture(target, texture);
        glTexImage2D(target, 0, info.internal, data.width, data.height, 0, info.format, GL_UNSIGNED_BYTE, data.data);
        glGenerateMipmap(target);
        SetParameters(target, info.texture_map);
        image->free();
    }
} // textures
// graphics
// tri