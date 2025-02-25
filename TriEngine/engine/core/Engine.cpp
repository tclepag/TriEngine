//
// Created by lepag on 2/25/25.
//

#include "Engine.h"

#include <iostream>
#include <ostream>
#include <glad/glad.h>

namespace tri::core {
    Engine::Engine() {
        glfwInit();
    }

    Engine::~Engine() {
        std::cout << "ENGINE CLOSING" << std::endl;
    }

    
    void Engine::Start() {
        auto* MainWindow = new Window(nullptr, 800, 600, "TriEngine");
        mainWindow = MainWindow;

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        while (running) {
            glfwPollEvents();
            Update();
        }

        Close();
    }

    void Engine::Update() {
        if (mainWindow->isTerminating()) {
            running = false;
            return;
        }

        mainWindow->update();
    }

    void Engine::Render() {
    }

    void Engine::Close() {

    }
} // core
// tri