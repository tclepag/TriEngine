//
// Created by lepag on 2/21/25.
//

#ifndef ALUAENVIORNMENT_H
#define ALUAENVIORNMENT_H

#include <functional>
#include <vector>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "ALuaScript.h"

namespace tri::lua {

class ALuaEnvironment {
public:
    using ALuaPtr = std::unique_ptr<ALuaScript>;
    using ALuaState = std::unique_ptr<lua_State>;
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
    void luaExpose(const int* integer);
    // Exposes a C++ boolean to lua
    void luaExpose(bool boolean);
    // Exposes a C++ string to lua
    void luaExpose(const char* string);
    // Exposes a C++ float to lua
    void luaExpose(const float* floating);
    template<typename Result, typename... Args>
    // Exposes a C++ Function to lua
    void luaExpose(std::function<Result(Args...)> cFunction);
    template<class CClass>
    // Calls the static C++ luaInit function to construct
    // a lua version of the C++ class provided
    void luaExpose(CClass cClass);

    void newLuaClass(const char* className);
    void setLuaField(int index, const char* fieldName);
    void setLuaGlobal(const char* globalName);

    void releaseLua(ALuaPtr lua);
    void free();
protected:
    ALuaState* p_state = nullptr;
    std::vector<ALuaScript*> scripts;
};

} // lua
// tri

#endif //ALUAENVIORNMENT_H
