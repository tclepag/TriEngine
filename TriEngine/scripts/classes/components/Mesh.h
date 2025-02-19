//
// Created by lepag on 2/16/2025.
//

#ifndef MESH_HPP
#define MESH_HPP

#include "ActorComponent.h"
#include "../../graphics/ObjectBuffer.h"
#include "../../graphics/Shader.h"
#include "../../util/Time.h"
#include "../../graphics/textures/Texture2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace tri {

class Mesh : public ActorComponent {
public:
    void init() override;
    void start() override;
    void update() override;
    void draw(core::Screen* from) override;
    void addTexture(graphics::textures::Texture2D* texture);
protected:
    graphics::textures::Texture2D* texture;
    graphics::ObjectBuffer*buffer = nullptr;
    graphics::ShaderProgram*shaderProgram = nullptr;
};

} // tri

#endif //MESH_HPP
