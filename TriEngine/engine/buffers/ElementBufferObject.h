//
// Created by TC on 2/18/2025.
//

#ifndef ELEMENTBUFFEROBJECT_H
#define ELEMENTBUFFEROBJECT_H

#include <glad/glad.h>

namespace tri::buffers {
    class ElementBufferObject {
    public:
        GLuint id;

        ElementBufferObject(): id(0) {
          glGenBuffers(1, &id);
        }

        ~ElementBufferObject() {
          glDeleteBuffers(1, &id);
        }

        void bind() const {
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        }

        void upload(std::vector<int>& indices, GLenum drawType) {
          auto isize = static_cast<GLsizeiptr>(indices.size() * sizeof(int));
          glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, indices.data(), drawType);
        }

        void unbind() {
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        void dispose() {
          delete this;
        }
    };
}

#endif //ELEMENTBUFFEROBJECT_H
