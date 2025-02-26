//
// Created by lepag on 2/25/25.
//

#include "Engine.h"

#include <iostream>
#include <ostream>

namespace tri::core {
    Engine* Engine::engine = nullptr;

    Engine::Engine() {
        glfwInit();

        onStart = new common::EventDispatcher<int>();
        onQuit = new common::EventDispatcher<int>();

        pyCore = PyCore::GetCore();
        pyCore->Start();

        pyManager = &APyManager::GetManager();
    }

    Engine::~Engine() {
        std::cout << "ENGINE CLOSING" << std::endl;

        pyCore->Stop();
        pyManager->Free();
        mainWindow->terminate();
    }
    
    void Engine::Start() {
        auto* MainWindow = new Window(nullptr, 800, 600, "TriEngine");
        mainWindow = MainWindow;

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        onStart->out(1);

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
        onQuit->out(1);
    }
} // core
// tri