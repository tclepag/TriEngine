//
// Created by lepag on 2/18/2025.
//

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "BaseTextureClass.h"

namespace tri::graphics::textures {

class Texture2D : public BaseTextureClass {
public:
    struct TX2D {
        GLenum internal = GL_RGBA;
        GLenum format = GL_RGBA;
        TextureMap texture_map = {
            {GL_TEXTURE_MIN_FILTER, GL_NEAREST},
            {GL_TEXTURE_MAG_FILTER, GL_NEAREST},
            {GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE},
            {GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE},
        };
    };
    Texture2D(util::Image* image, const TX2D& info);
    ~Texture2D() = default;
};

} // textures
// graphics
// tri

#endif //TEXTURE2D_H
