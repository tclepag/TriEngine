//
// Created by lepag on 2/23/2025.
//

#include "ALuaManager.h"

#include <ranges>


namespace tri::lua {
    ALuaManager * ALuaManager::SGetInstance() {
        static ALuaManager Instance;
        return &Instance;
    }

    bool ALuaManager::DoesStateExist(const char* StateName) {
        for (auto State: LuaStates) {
            if (State->Name == StateName) {
                return true;
            }
        }
        return false;
    }

    ALuaManager::ALuaManager() = default;

    ALuaManager::~ALuaManager() {
        for (auto State: LuaStates) {
            delete State;
        }
    }

    void ALuaManager::Register(const char *StateName, const std::function<void(ALuaState* LuaState)>& initFunc) {
        if (DoesStateExist(StateName)) {
            return;
        }
        const auto L = new ALuaState(StateName);
        if (initFunc) {
            initFunc(L);
        }
        LuaStates.emplace_back(L);
    }

    void ALuaManager::Unregister(const char *StateName) {
        for (auto State: LuaStates) {
            if (State->Name == StateName) {
                delete State;
            }
        }
    }

    ALuaState* ALuaManager::GetState(const char *StateName) {
        for (auto State: LuaStates) {
            if (State->Name == StateName) {
                return State;
            }
        }
        return nullptr;
    }

    ALuaState* ALuaManager::GetState(const lua_State *LuaState) {
        for (auto State: LuaStates) {
            if (State->GetLuaState() == LuaState) {
                return State;
            }
        }
        return nullptr;
    }

    std::vector<ALuaState*> ALuaManager::GetStates() {
        return LuaStates;
    }

    void ALuaManager::Call(const States& States, const std::function<void(ALuaState* LuaState)>& Callback) {
        for (auto StateName: States) {
            if (auto State = GetState(StateName)) {
                Callback(State);
            }
        }
    }

    void ALuaManager::CallAll(const std::function<void(ALuaState* LuaState)>& Callback) {
        for (auto State: LuaStates) {
            Callback(State);
        }
    }

} // lua
// tri