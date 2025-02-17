#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "TriEngine/scripts/core/Screen.hpp"
#include "TriEngine/scripts/classes/Actor.hpp"
#include "TriEngine/scripts/classes/components/Mesh.hpp"

using namespace tri;
using namespace core;

void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    SetDllDirectory("..\\bin");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(error_callback);

    auto* mainScreen = new Screen(
        800,
        600,
        "TestApp"
    );

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        mainScreen->close();
        glfwTerminate();
        return -1;
    }

    auto* new_actor = new Actor(nullptr);
    auto* mesh = new Mesh();
    new_actor->attachComponent(mesh);

    glEnable(GL_DEPTH_TEST);

    while (!mainScreen->windowClosing()) {
        if (glfwGetKey(mainScreen->wnd(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            mainScreen->windowToClose(true);
        }

        // Clear the background buffer and set the background color to black
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        new_actor->draw();

        // The drawing was done in the background buffer
        // We swap our buffers to show the results
        glfwSwapBuffers(mainScreen->wnd());
        glfwPollEvents();
    }

    mainScreen->close();
    glfwTerminate();
    return 0;
}