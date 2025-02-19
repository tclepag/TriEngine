//
// Created by lepag on 2/16/2025.
//

#ifndef OBJECTBUFFER_HPP
#define OBJECTBUFFER_HPP

#include <vector>
#include <glad/glad.h>

#include "../buffers/VertexArrayObject.h"
#include "../buffers/VertexBufferObject.h"
#include "../buffers/ElementBufferObject.h"



namespace tri::graphics {

class ObjectBuffer {
    public:
      buffers::VertexArrayObject* VAO{};
      buffers::VertexBufferObject* VBO{};
      buffers::ElementBufferObject* EBO{};

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
