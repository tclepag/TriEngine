#include <iostream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "TriEngine/engine/lua/ALuaManager.h"


void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int greet(lua_State* L) {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

int main() {
    auto* luaManager = tri::lua::ALuaManager::SGetInstance();


    luaManager->Register("Core", nullptr);
    luaManager->Register("Development", nullptr);
    luaManager->Register("Game", [](const tri::lua::ALuaState* state) {
        state->Push();
        state->SetGlobal("os");

        state->Push();
        state->SetGlobal("io");
    });

    // Establish Globals
    luaManager->Call({"Core", "Development", "Game"}, [luaManager](const tri::lua::ALuaState* state) {
        state->Push(greet);
        state->SetGlobal("HELLO_WORLD");

        state->LuaFile("lua/Test.lua");
    });

    for (auto State: luaManager->GetStates()) {
        std::cout << State->Name << " " << State->GetLuaState() << std::endl;
    }

    return 0;
}
