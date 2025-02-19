//
// Created by lepag on 2/18/2025.
//

#ifndef TEXTURE3D_H
#define TEXTURE3D_H

#include "BaseTextureClass.h"

namespace tri::graphics::textures {

    class Texture3D : public BaseTextureClass {
    public:
        struct TX3D {
            GLint internal;
            GLint format;
            int depth = 0;
            TextureMap texture_map;
        };
        Texture3D(util::Image* image, const TX3D& info);
        ~Texture3D() = default;
    };

} // textures
// graphics
// tri

#endif //TEXTURE3D_H
