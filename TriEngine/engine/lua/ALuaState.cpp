//
// Created by lepag on 2/23/2025.
//

#include "ALuaState.h"

#include <iostream>
#include <utility>

#include "ALuaManager.h"


namespace tri::lua {
    ALuaState::ALuaState(std::string Name) {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        this->L = L;
        this->Name = std::move(Name);
    }

    ALuaState::~ALuaState() {
        lua_close(L);
    }

    void ALuaState::Push() const {
        lua_pushnil(L);
    }

    void ALuaState::Push(const char *String) const {
        lua_pushstring(L, String);
    }

    void ALuaState::Push(float Float) const {
        lua_pushnumber(L, Float);
    }

    void ALuaState::Push(double Double) const {
        lua_pushnumber(L, Double);
    }

    void ALuaState::Push(int Int) const {
        lua_pushnumber(L, Int);
    }

    void ALuaState::Push(bool Bool) const {
        lua_pushboolean(L, Bool);
    }

    void ALuaState::Push(lua_CFunction func) const {
        lua_pushcfunction(L, func);
    }

    bool ALuaState::IsNumber(int Index) const {
        return lua_isnumber(L, Index);
    }

    bool ALuaState::IsInt(int Index) const {
        return lua_isinteger(L, Index);
    }

    bool ALuaState::IsString(int Index) const {
        return lua_isstring(L, Index);
    }

    bool ALuaState::IsBool(int Index) const {
        return lua_isboolean(L, Index);
    }

    bool ALuaState::IsTable(int Index) const {
        return lua_istable(L, Index);
    }

    const char * ALuaState::ToString(int Index) const {
        return lua_tostring(L, Index);
    }

    int ALuaState::ToInt(int Index) const {
        return lua_tointeger(L, Index);
    }

    double ALuaState::ToNumber(int Index) const {
        return lua_tonumber(L, Index);
    }

    bool ALuaState::ToBool(int Index) const {
        return lua_toboolean(L, Index);
    }

    void ALuaState::Pop(int Index) const {
        lua_pop(L, Index);
    }

    void ALuaState::SetTable(int Index) const {
        lua_settable(L, Index);
    }

    void ALuaState::GetTable(int Index) const {
        lua_gettable(L, Index);
    }

    void ALuaState::GetGlobal(const char *String) const {
        lua_getglobal(L, String);
    }

    void ALuaState::SetGlobal(const char *String) const {
        lua_setglobal(L, String);
    }

    void ALuaState::GetMetaTable(int Index) const {
        lua_getmetatable(L, Index);
    }

    void ALuaState::NewMetaTable(const char *MetaTableName) const {
        lua_setmetatable(L, -2);
    }

    void ALuaState::LuaFile(const char *filePath) const {
        int result = luaL_dofile(L, filePath);
        if (result != 0) {
            std::cerr << "ERROR RUNNING LUA FILE AT [" << filePath << "]" << std::endl;
            std::cerr << "LUA ERROR: " << lua_tostring(L, -1) << std::endl;
        }
    }

    template<class Class>
    void ALuaState::RegisterClass() {
        if (Class::RegisterLua) {
            Class::RegisterLua(this, [this](const LuaClass& classData) {
                // Create new meta
                NewMetaTable(classData.name);

                // Setup destructor
                Push("__gc");
                Push(classData.Destructor);
                SetTable(-3);

                for (auto [first, second]: classData.Methods) {
                    if (first == nullptr && second == nullptr) {
                        break;
                    }
                    Push(first);
                    Push(second);
                    SetTable(-3);
                }

                // Remove metaTable from lua stack
                Pop();

                // Register the classes constructor in global environment
                Push(classData.name);
                Push(classData.Constructor);
                SetGlobal(classData.name);
            });
        }
    }

    template<typename Result, typename ... Args>
    std::tuple<Result, ALuaState::LuaFuncReturn> ALuaState::Call(const int error, Args... args) {
        (Push(std::forward<Args>(args)), ...);

        int lua_result = lua_pcall(L, sizeof...(args), 1, error);
        LuaFuncReturn result;

        std::tuple<Result, LuaFuncReturn> value;

        switch (lua_result) {
            case LUA_OK:
                result = SUCCESS;
                break;
            case LUA_ERRRUN:
                result = FAIL;
                break;
            case LUA_ERRMEM:
                result = MEMFAIL;
                break;
            default: ;
        }

        if (IsBool()) {
            value = std::make_tuple(ToBool(), result);
        }

        if (IsInt()) {
            value = std::make_tuple(ToInt(), result);
        }

        if (IsNumber()) {
            value = std::make_tuple(ToNumber(), result);
        }

        if (IsString()) {
            value = std::make_tuple(ToString(), result);
        }

        return value;
    }

    lua_State* ALuaState::GetLuaState() const {
        return L;
    }
} // lua
// tri