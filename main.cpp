#include <iostream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "TriEngine/engine/core/Engine.h"

using namespace tri::core;

void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main() {
    {
        auto* Engine = Engine::GetEngine();
        Engine->Start();
    }
    std::cout << "Goodbye!" << std::endl;
    return 0;
}
