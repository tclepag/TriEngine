//
// Created by lepag on 2/16/2025.
//

#include "Mesh.h"

// Vertices coordinates
std::vector vertices = {
    // positions          // colors           // texture coords
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
};

// Indices for vertices order
std::vector indices = {
    0, 1, 2,
    2, 3, 0// One triangle formed by vertices 0, 1, and 2
};

namespace tri {
    void Mesh::init() {
        buffer = new graphics::ObjectBuffer(
            vertices,
            indices
        );

        shaderProgram = new graphics::ShaderProgram(
       "content/shaders/default.vert",
       "content/shaders/default.frag"
       );
    }

    void Mesh::start() {
        shaderProgram->use();
    }

    void Mesh::update() {

    }

    void Mesh::addTexture(graphics::textures::Texture2D *texture) {
        this->texture = texture;
    }

    void Mesh::draw(core::Screen* from) {
        shaderProgram->use();

        if (texture) {
            texture->bind();
        }

        float currentTime = util::Time::GetElapsedTime();
        float rotate_speed = 150.0f;
        float float_speed = 1.0f;
        float float_distance = 0.2f;

        auto model = glm::mat4(1.0f);
        auto view = glm::mat4(1.0f);
        auto projection = glm::mat4(1.0f);

        view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
        projection = glm::perspective(glm::radians(45.0f), from->aspectRatio(), 0.1f, 100.0f);
        model = glm::translate(model, glm::vec3(0.0f, (sin(currentTime * float_speed) * float_distance) - 1.0f, -5.0f));
        //model = glm::rotate(model, currentTime * glm::radians(rotate_speed), glm::vec3(0.5f, 0.5f, 0.5f));

        float origin_scale = 2.0f;
        float size = 0.1;
        float scale_speed = 1.5f;
        float scale_distance = 0.9f;

        size = origin_scale + sin(currentTime * scale_speed) * scale_distance;

        shaderProgram->uniformMat4("model", model);
        shaderProgram->uniformMat4("view", view);
        shaderProgram->uniformMat4("projection", projection);
        shaderProgram->uniformFloat("time", currentTime);
        shaderProgram->uniformFloat("size", size);

        buffer->use();
    }
} // tri