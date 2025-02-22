//
// Created by lepag on 2/21/25.
//

#ifndef ALUAENVIORNMENT_H
#define ALUAENVIORNMENT_H

#include <functional>
#include <vector>

#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>
#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>
#include "ALuaScript.h"

namespace tri::lua {

class ALuaEnvironment {
public:
    using ALuaPtr = std::unique_ptr<ALuaScript>;
    using ALuaState = lua_State*;
    using ALuaScripts = std::vector<ALuaPtr>;
    struct LuaContext {
        ALuaPtr* script;
    };

    ALuaEnvironment();
    ~ALuaEnvironment();

    ALuaPtr* loadLua(const std::string& lua_path);
    ALuaScripts* getLuaScripts();
    ALuaState& getLuaState();

    // Exposes a C++ integer to lua
    void luaSet(const int *integer) const;
    // Exposes a C++ boolean to lua
    void luaSet(bool boolean) const;
    // Exposes a C++ string to lua
    void luaSet(const char *string) const;
    // Exposes a C++ float to lua
    void luaSet(const float *floating) const;
    template<class Result, typename... Args>
    // Exposes a C++ Function to lua with arguments
    void luaSet(std::function<Result(Args...)> cFunction);
    template<class CClass>
    // Calls the static C++ luaInit function to construct
    // a lua version of the C++ class provided
    void luaConstructClass(CClass cClass);

    template<typename Result, typename... Args>
    std::function<Result*(Args...)> wrapCFunction(Result (cFunction)(Args...));

    void newLuaClass(const char* className) const;
    void setLuaTable(int index) const;
    void setLuaField(int index, const char* fieldName) const;
    void setLuaGlobal(const char* globalName) const;
    template<class CClass>
    CClass* createUserDataFromClass(CClass* cClass);
    void releaseLua(const ALuaScript* lua);
    void free() const;

protected:
    ALuaState p_state;
    ALuaScripts scripts;
};

} // lua
// tri

#endif //ALUAENVIORNMENT_H
