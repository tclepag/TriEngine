//
// Created by lepag on 2/25/25.
//

#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"

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

    void Start();
    void Update();
    void Render();
    void Close();
private:
    bool running = true;
    static Engine* engine;

    Windows windows;
    Window* mainWindow;

    Engine();
    ~Engine();
};

} // core
// tri

#endif //ENGINE_H
