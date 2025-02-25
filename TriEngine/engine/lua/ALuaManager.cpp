//
// Created by lepag on 2/24/25.
//

#include "ALuaManager.h"

namespace tri::lua {
    ALuaManager & ALuaManager::Instance() {
        static ALuaManager instance;
        return instance;
    }

    ALuaManager::LuaObject ALuaManager::CreateLuaEnvironment(const char *EnvName, const LuaCallback& Callback) {
        LuaObject LuaState = std::make_shared<sol::state>();
        LuaState->open_libraries(sol::lib::base);
        LuaReg.emplace_back(LuaState);

        if (Callback) {
            Callback(LuaState);
        }

        return LuaState;
    }

    void ALuaManager::RunAllEnvironments(const LuaCallback& Callback) {
        for (const auto& State: LuaReg) {
            Callback(State);
        }
    }

    ALuaManager::ALuaManager() = default;

    ALuaManager::~ALuaManager() {
        for (auto& State: LuaReg) {
            State.reset();
        }
    }
}
