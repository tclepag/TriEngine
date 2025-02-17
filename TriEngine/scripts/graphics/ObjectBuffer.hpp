//
// Created by lepag on 2/16/2025.
//

#ifndef OBJECTBUFFER_HPP
#define OBJECTBUFFER_HPP

#include <vector>
#include <glad/glad.h>


namespace tri::graphics {

class ObjectBuffer {
    public:
      GLuint VAO{}, VBO{}, EBO{};
      std::vector<float> vertices;
      std::vector<int> indices;

      ObjectBuffer(const std::vector<float>& vertices, const std::vector<int>& indices);
      ~ObjectBuffer();
      void rebuild();
      void use() const;
};

} // graphics
// tri

#endif //OBJECTBUFFER_HPP
