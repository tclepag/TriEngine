//
// Created by lepag on 2/16/2025.
//

#ifndef MESH_HPP
#define MESH_HPP

#include "ActorComponent.hpp"
#include "../../core/Screen.hpp"
#include "../../graphics/ObjectBuffer.hpp"
#include "../../graphics/Shader.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace tri {

class Mesh : public ActorComponent {
public:
    void init() override;
    void start() override;
    void update() override;
    void draw() override;
protected:
    graphics::ObjectBuffer* buffer;
    graphics::ShaderProgram* shaderProgram;
};

} // tri

#endif //MESH_HPP
