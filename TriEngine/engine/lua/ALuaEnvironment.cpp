//
// Created by lepag on 2/21/25.
//

#include "ALuaEnvironment.h"


namespace tri::lua {
    ALuaEnvironment::ALuaEnvironment() {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        p_state = L;
    }

    ALuaEnvironment::~ALuaEnvironment() {
        if (p_state) {
            lua_close(p_state);
        }
    }

    ALuaEnvironment::ALuaPtr * ALuaEnvironment::loadLua(const std::string &lua_path) {
        if (luaL_dofile(p_state, lua_path.c_str()) != 0) {
            // If there's an error, print the error message
            std::cerr << "Error loading Lua file: " << lua_tostring(p_state, -1) << std::endl;
            lua_pop(p_state, 1);  // Remove the error message from the stack
        }
    }

    ALuaEnvironment::ALuaScripts * ALuaEnvironment::getLuaScripts() {
        return &scripts;
    }

    ALuaEnvironment::ALuaState & ALuaEnvironment::getLuaState() {
        return p_state;
    }

    void ALuaEnvironment::luaSet(const int *integer) const {
        lua_pushinteger(p_state, *integer);
    }

    void ALuaEnvironment::luaSet(const bool boolean) const {
        lua_pushboolean(p_state, boolean);
    }

    void ALuaEnvironment::luaSet(const char *string) const {
        lua_pushstring(p_state, string);
    }

    void ALuaEnvironment::luaSet(const float *floating) const {
        lua_pushnumber(p_state, *floating);
    }

    template<typename Result, typename ... Args>
    void ALuaEnvironment::luaSet(std::function<Result(Args...)> cFunction) {
        lua_pushcfunction(p_state, cFunction);
    }

    template<class CClass>
    void ALuaEnvironment::luaConstructClass(CClass cClass) {
        cClass.luaInit(this);
    }

    template<typename Result, typename... Args>
    std::function<Result *(Args...)> ALuaEnvironment::wrapCFunction(Result (cFunction)(Args...)) {
        return std::function<Result*(Args...)>(cFunction);
    }

    void ALuaEnvironment::newLuaClass(const char *className) const {
        luaL_newmetatable(p_state, className);
        lua_pushstring(p_state, "__index");
        lua_newtable(p_state);
    }

    void ALuaEnvironment::setLuaTable(int index) const {
        lua_settable(p_state, index);
    }

    void ALuaEnvironment::setLuaField(int index, const char *fieldName) const {
        lua_setfield(p_state, index, fieldName);
    }

    void ALuaEnvironment::setLuaGlobal(const char *globalName) const {
        lua_setglobal(p_state, globalName);
    }

    template<class CClass>
    CClass *ALuaEnvironment::createUserDataFromClass(CClass *cClass) {
        auto** userData = static_cast<CClass **>(lua_newuserdata(p_state, sizeof(CClass*)));
        *userData = cClass;
        return userData;
    }

    void ALuaEnvironment::releaseLua(const ALuaScript* lua) {
        for (auto& lua_ptr : scripts) {
            if (lua_ptr.get() == lua) {
                lua_ptr.reset();
            }
        }
    }

    void ALuaEnvironment::free() const {
        delete this;
    }
} // lua
// tri