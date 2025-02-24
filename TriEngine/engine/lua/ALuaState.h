//
// Created by lepag on 2/24/25.
//

#ifndef ALUASTATE_H
#define ALUASTATE_H

#include <unordered_map>
#include <variant>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


namespace tri::lua {
    class ALuaState {
        using LuaValue = std::variant<int, float, char*, bool>;
        using LuaTable = std::unordered_map<const char*, LuaValue>;


    protected:
        lua_State* L;

    };
}



#endif //ALUASTATE_H
