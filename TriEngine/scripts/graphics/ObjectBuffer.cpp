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
        if (VAO != 0) {
            glDeleteVertexArrays(1, &VAO);
        }
        if (VBO != 0) {
            glDeleteBuffers(1, &VBO);
        }
        if (EBO != 0) {
            glDeleteBuffers(1, &EBO);
        }
        glGenBuffers(1, &EBO); // Create Element Buffer Object
        glGenVertexArrays(1, &VAO); // Create Vertex Array Object
        glGenBuffers(1, &VBO); // Create Vertex Buffer Object

        glBindVertexArray(VAO); // Bind the Vertex Array Object


        // Bind Vertex Buffer Object and transfer vertex data to the Vertex Array Object
        auto vsize = static_cast<GLsizeiptr>(vertices.size() * sizeof(float));

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vsize, vertices.data(), GL_STATIC_DRAW);

        // Bind Element Buffer Object and load our indices.
        // Helpful since instead of specifying vertice position,
        // we use ints and OpenGL just gets the vertex position by finding it with the index
        // Like: vertices[index]
        auto isize = static_cast<GLsizeiptr>(indices.size() * sizeof(int));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, indices.data(), GL_STATIC_DRAW);

        // Position attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Color Attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Texture Coordinate Attribute
        //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        //glEnableVertexAttribArray(2);

        // Unbind Vertex Buffer Object and Vertex Array Object
        // Good practice to unbind after creation
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void ObjectBuffer::use() const {
        auto isize = static_cast<GLsizei>(indices.size() * sizeof(int));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, isize/sizeof(int), GL_UNSIGNED_INT, nullptr);  // Use indices to draw
        glBindVertexArray(0);
    }



} // graphics
// tri