//
// Created by lepag on 2/23/2025.
//

#ifndef ALUASTATE_H
#define ALUASTATE_H

#define LUA_STATIC
#include <lua.hpp>
#include <string>

#include <unordered_map>


namespace tri::lua {

class ALuaState {
public:
    enum Types {
        NUMBER,
        STRING,
        BOOL,
        TABLE
    };

    enum LuaFuncReturn {
        SUCCESS, // No errors
        FAIL, // Function error
        MEMFAIL, // Memory Allocation error
        GCFAIL // Garbage Collection error
    };

    enum LuaFileReadResult {
        OK,
        ERR,
    };

    struct LuaClass {
        const char* name;
        lua_CFunction Constructor;
        lua_CFunction Destructor;

        std::unordered_map<const char*, void*> Methods;
    };

    ALuaState(std::string Name);
    ~ALuaState();

    // Pushes nil into the Lua Stack
    void Push() const;
    // Pushes a string into the Lua Stack
    void Push(const char* String) const;
    // Pushes a float into the Lua Stack
    // Floats in Lua are converted to doubles for precision
    void Push(float Float) const;
    // Pushes a double into the Lua Stack
    void Push(double Double) const;
    // Pushes an int into the Lua Stack
    void Push(int Int) const;
    // Pushes a bool into the Lua Stack
    void Push(bool Bool) const;
    // Pushes a C++ Function into the Lua Stack
    void Push(lua_CFunction func) const;

    bool IsNumber(int Index = -1) const;
    bool IsInt(int Index = -1) const;
    bool IsString(int Index = -1) const;
    bool IsBool(int Index = -1) const;
    bool IsTable(int Index = -1) const;

    const char* ToString(int Index = -1) const;
    int ToInt(int Index = -1) const;
    double ToNumber(int Index = -1) const;
    bool ToBool(int Index = -1) const;

    void Pop(int Index = 1) const;

    void SetTable(int Index = -1) const;
    void GetTable(int Index = -1) const;

    // Gets the value in _G
    void GetGlobal(const char* String) const;
    // Sets _G value in Lua State
    void SetGlobal(const char* String) const;

    void GetMetaTable(int Index = -1) const;
    void NewMetaTable(const char* MetaTableName) const;

    void LuaFile(const char* filePath) const;

    template <class Class>
    void RegisterClass();

    // Calls a function
    template <typename Result, typename... Args>
    std::tuple<Result, LuaFuncReturn> Call(int error = 0, Args...);

    lua_State* GetLuaState() const;

    std::string Name;
private:
    lua_State* L;
};

} // lua
// tri

#endif //ALUASTATE_H
