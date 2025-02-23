//
// Created by lepag on 2/21/25.
//

#ifndef ALUAENVIRONMENT_H
#define ALUAENVIRONMENT_H

#include <functional>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

namespace tri::lua {

class ALuaEnvironment {
public:
    using ALuaState = lua_State*;
    ALuaEnvironment();
    ~ALuaEnvironment();

    ALuaState* getLuaState();

    void pushValue(int* integer);
    void pushValue(float* number);
    void pushValue(double* number);
    void pushValue(bool* boolean);
    void pushValue(const char* string);
    template<typename Return, typename... Args>
    void pushValue(std::function<Return*(Args...)> cFunction);

    void registerLuaClass(const char* className);
private:
    ALuaState* m_luaState;
};

} // lua
// tri

#endif //ALUAENVIRONMENT_H
