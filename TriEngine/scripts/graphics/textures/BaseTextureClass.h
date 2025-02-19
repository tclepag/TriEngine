//
// Created by lepag on 2/18/2025.
//

#ifndef BASETEXTURECLASS_H
#define BASETEXTURECLASS_H

#include <unordered_map>
#include <glad/glad.h>
#include "../../util/Image.h"
namespace tri::graphics::textures {
class BaseTextureClass {
    public:
      typedef std::unordered_map<GLenum, GLint> TextureMap;
      GLuint texture;
      GLenum target;
       BaseTextureClass() = default;
      ~BaseTextureClass();

      void free();
      void bind();
      void unbind();
      void SetParameters(GLenum target, TextureMap texture_map);
};

} // textures
// graphics
// tri

#endif //BASETEXTURECLASS_H
