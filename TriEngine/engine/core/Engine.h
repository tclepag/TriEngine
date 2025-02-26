//
// Created by lepag on 2/25/25.
//

#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>

#include "Engine.h"
#include "PyCore.h"
#include "Window.h"
#include "../common/EventDispatcher.h"
#include "../py/APyManager.h"

namespace tri::core {

class Engine {
public:
    using Windows = std::vector<std::shared_ptr<Window>>;
    static Engine* GetEngine() {
        Engine* Instance = engine;
        if (!Instance) {
            Instance = new Engine();
            engine = Instance;
        }
        return Instance;
    }

    common::EventDispatcher<int> *onStart;
    common::EventDispatcher<int> *onQuit;

    void Start();
    void Update();
    void Render();
    void Close();
private:
    bool running = true;
    static Engine* engine;

    Windows windows;
    Window* mainWindow;
    APyManager* pyManager;
    PyCore* pyCore;

    Engine();
    ~Engine();
};

} // core
// tri

#endif //ENGINE_H
