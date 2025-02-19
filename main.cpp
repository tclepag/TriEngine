#include <iostream>

#include <glad/glad.h>
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
#include "TriEngine/scripts/util/Time.h"
#include "TriEngine/scripts/graphics/textures/Texture2D.h"

using namespace tri;
using namespace core;

void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    auto* time = new util::Time();

    WNDCLASSEX wcex = {0};
    wcex.hInstance = hInstance;
    wcex.lpszClassName = "mainWindowClass";
    Screen::createWindowClass(wcex);

    Screen::ScreenInfo screenInfo = {};
    screenInfo.width = 800;
    screenInfo.height = 600;
    screenInfo.title = "TriEngine";
    screenInfo.className = "mainWindowClass";

    auto* screen = new Screen(screenInfo);

    screen->makeCurrent();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(wglGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    auto* actor = new Actor(nullptr);
    auto* mesh = new Mesh();

    actor->attachComponent(mesh);

    glEnable(GL_DEPTH_TEST);

    auto* image = new util::Image("content/images/texture_test.png", util::Image::STB);

    graphics::textures::Texture2D::TX2D info = {};

    auto* texture_test = new graphics::textures::Texture2D(image, info);

    mesh->addTexture(texture_test);

    while (true) {
        bool result = screen->message();
        if (result) {
            if (screen->msg.message == WM_QUIT) {
                break;
            }
        } else {
            Sleep(10);
        }

        std::cout << result << std::endl;
        screen->dispatch();
        // Render stuff here
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RECT clientRect;
        GetClientRect(screen->hWnd, &clientRect);
        int width = clientRect.right - clientRect.left;
        int height = clientRect.bottom - clientRect.top;

        glViewport(0, 0, width, height);

        actor->draw(screen);

        SwapBuffers(screen->hdc);
    }

    texture_test->free();
    actor->detachComponent(mesh);
    delete actor;

    for (const auto& className : Screen::classNames) {
        UnregisterClass(className.c_str(), hInstance);
    }
    return static_cast<int>(screen->msg.wParam);
}