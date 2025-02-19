//
// Created by lepag on 2/16/2025.
//

#include "ObjectBuffer.h"

#include <iostream>
#include <ostream>
#include <utility>


namespace tri::graphics {
    ObjectBuffer::ObjectBuffer(const std::vector<float>& vertices, const std::vector<int>& indices) {
        this->vertices = vertices;
        this->indices = indices;

        rebuild();
    }

    void ObjectBuffer::rebuild() {
        delete VAO;
        delete VBO;
        delete EBO;

        VAO = new buffers::VertexArrayObject();
        VBO = new buffers::VertexBufferObject();
        EBO = new buffers::ElementBufferObject();

        VAO->bind();

        VBO->bind();
        VBO->upload(vertices, GL_DYNAMIC_DRAW);

        EBO->bind();
        EBO->upload(indices, GL_DYNAMIC_DRAW);
        // Position Attribute (Index 0)
        VAO->attribute(0, 3, 8, 0); // 3 floats at offset 0
        VAO->enableAttribute(0);

        // Color Attribute (Index 1)
        VAO->attribute(1, 3, 8, 3); // 3 floats at offset 3
        VAO->enableAttribute(1);

        // Texture Coordinate Attribute (Index 2)
        VAO->attribute(2, 2, 8, 6); // 2 floats at offset 6 (not 3!)
        VAO->enableAttribute(2);

        // Good practice to unbind after creation
        VAO->unbind();
        VBO->unbind();
        EBO->unbind();
    }

    void ObjectBuffer::use() const {
        auto isize = static_cast<GLsizei>(indices.size() * sizeof(int));
        VAO->bind();
        glDrawElements(GL_TRIANGLES, isize/sizeof(int), GL_UNSIGNED_INT, nullptr);  // Use indices to draw
        VAO->unbind();
    }



} // graphics
// tri