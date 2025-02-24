//
// Created by TC on 2/21/25.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../utility/Image.h"

namespace tri::core {

class Window {
public:
    explicit Window(
        Window* parent = nullptr,
        int width = 800,
        int height = 600,
        std::string title = "Window",
        std::string icon = "content/images/app.bmp"
        );
    ~Window();

    glm::vec2 getDimensions();
    [[nodiscard]] float getAspectRatio() const;

    void update();
    void render();

    void processInput();

    void terminate() const;
    [[nodiscard]] bool isTerminating() const;
protected:
    GLFWwindow* p_window;
    Window* p_parent;
};

} // core
// tri

#endif //WINDOW_H
