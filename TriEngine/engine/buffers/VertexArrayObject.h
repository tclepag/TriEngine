//
// Created by lepag on 2/18/2025.
//

#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

#include <glad/glad.h>

namespace tri::buffers {
    class VertexArrayObject {
    public:
        GLuint id;

        VertexArrayObject(): id(0) {
            glGenVertexArrays(1, &id);
        }

        ~VertexArrayObject() {
            glDeleteVertexArrays(1, &id);
        }

        void bind() const {
            glBindVertexArray(id);
        }

        void unbind() {
            glBindVertexArray(0);
        }

        void attribute(int ind, int size, GLsizei stride, int offset) {
            glVertexAttribPointer(ind, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), reinterpret_cast<void *>(offset * sizeof(float)));
        }

        void enableAttribute(int ind) {
            glEnableVertexAttribArray(ind);
        }

        void disableAttribute(int ind) {
            glDisableVertexAttribArray(ind);
        }

        void dispose() {
            delete this;
        }
    };
}

#endif //VERTEXARRAYOBJECT_H
