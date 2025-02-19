//
// Created by lepag on 2/18/2025.
//

#include "BaseTextureClass.h"



namespace tri::graphics::textures {
    void BaseTextureClass::SetParameters(GLenum target, TextureMap texture_map) {
        for (auto [first, second] : texture_map) {
            glTexParameteri(target, first, second);
        }
    }

    BaseTextureClass::~BaseTextureClass() {
        glDeleteTextures(1, &texture);
    }

    void BaseTextureClass::free() {
        delete this;
    }

    void BaseTextureClass::bind() {
        glBindTexture(target, texture);
    }

    void BaseTextureClass::unbind() {
        glBindTexture(target, 0);
    }

} // textures
// graphics
// tri