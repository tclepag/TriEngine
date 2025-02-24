//
// Created by TC on 2/23/2025.
//

#ifndef LUAMANAGER_H
#define LUAMANAGER_H

#include <functional>
#include <unordered_map>
#include <algorithm>
#include <memory>

#define LUA_STATIC
#include <lua.hpp>

#include "ALuaState.h"

namespace tri::lua {

class ALuaManager {
public:
    using LuaPtr = std::shared_ptr<ALuaState>;
    using States = std::vector<const char*>;

    ALuaManager(const ALuaManager&) = delete;
    ALuaManager& operator=(const ALuaManager&) = delete;

    static ALuaManager* SGetInstance();

    bool DoesStateExist(const char* StateName);

    void Register(const char* StateName, const std::function<void(ALuaState* LuaState)>& initFunc);
    void Unregister(const char* StateName);

    ALuaState* GetState(const char* StateName);
    ALuaState* GetState(const lua_State* LuaState);

    std::vector<ALuaState*> GetStates();

    // Sends Lua States to the Callback
    // Usually used to help sync multiple Lua States
    void Call(const States& States, const std::function<void(ALuaState* LuaState)>& Callback);
    // Sends Lua States to the Callback
    // Usually used to help sync multiple Lua States
    void CallAll(const std::function<void(ALuaState* LuaState)>& Callback);
private:
    std::vector<ALuaState*> LuaStates{};

    ALuaManager();
    ~ALuaManager();
};

} // lua
// tri

#endif //LUAMANAGER_H
