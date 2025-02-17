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
#include <thread>
#include <mutex>

#include "TriEngine/scripts/core/Screen.h"
#include "TriEngine/scripts/classes/Actor.h"
#include "TriEngine/scripts/classes/components/Mesh.h"

using namespace tri;
using namespace core;

void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

std::mutex draw_mutex;
std::atomic<bool> renderReady(false);

Actor* new_actor = nullptr;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    auto* mainScreen = Screen::createMainInstance({
    800,
    600,
    "Main Window"
    });

    mainScreen->SetContextNew();

    PROC (*wglAddress)(LPCSTR) = wglGetProcAddress;

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(wglAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        mainScreen->Destroy();
        return -1;
    }

    new_actor = new Actor(nullptr);
    auto* mesh = new Mesh();
    new_actor->attachComponent(mesh);

    glEnable(GL_DEPTH_TEST);

    std::cout << "hi" << std::endl;

    while (mainScreen->NoPeekMessage().message != WM_QUIT) {
        MSG msg = mainScreen->GrabNewMessage();

        if (msg.message == WM_SIZE) {

        }

        mainScreen->Dispatch();
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        new_actor->draw();

        mainScreen->Swap();
    }

    wglMakeCurrent(nullptr, nullptr);

    mainScreen->Destroy();
    glfwTerminate();
    return 0;
}