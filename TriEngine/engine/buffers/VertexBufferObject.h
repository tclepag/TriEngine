//
// Created by TC on 2/18/2025.
//

#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include <glad/glad.h>

namespace tri::buffers {
    class VertexBufferObject {
    public:
        GLuint id;

        VertexBufferObject(): id(0) {
          glGenBuffers(1, &id);
        }

        ~VertexBufferObject() {
            glDeleteBuffers(1, &id);
        }

        void bind() const {
            glBindBuffer(GL_ARRAY_BUFFER, id);
        }

        void upload(std::vector<float> vertices, GLenum drawType) {
            auto vsize = static_cast<GLsizeiptr>(vertices.size() * sizeof(float));
            glBufferData(GL_ARRAY_BUFFER, vsize, vertices.data(), drawType);
        }

        void unbind() {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void dispose() {
            delete this;
        }
    };
}

#endif //VERTEXBUFFEROBJECT_H
