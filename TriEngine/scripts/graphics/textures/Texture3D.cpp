//
// Created by lepag on 2/18/2025.
//

#include "Texture3D.h"



namespace tri::graphics::textures {
    Texture3D::Texture3D(util::Image* image, const TX3D& info) : BaseTextureClass() {
        util::Image::ImageData data = image->getData();
        target = GL_TEXTURE_3D;
        glGenTextures(1, &texture);
        glBindTexture(target, texture);
        glTexImage3D(target, 0, info.internal, data.width, data.height, info.depth, 0, info.format, GL_UNSIGNED_BYTE, data.data);
        SetParameters(target, info.texture_map);
        image->free();
    }
} // textures
// graphics
// tri