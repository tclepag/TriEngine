#include <iostream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glad/glad.h>

#include "TriEngine/engine/core/Window.h"
#include "TriEngine/engine/ecs/entities/AActorBase.h"


void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main() {
    glfwInit();

    auto* window = new tri::core::Window(
        nullptr,
        800,
        600,
        "Hello World!"
    );

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }

    while (!window->isTerminating()) {
        glfwPollEvents();
    }

    window->terminate();

    return 0;
}
