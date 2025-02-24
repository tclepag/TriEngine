//
// Created by lepag on 2/24/25.
//

#ifndef ALUAMANAGER_H
#define ALUAMANAGER_H
#include <memory>
#include <vector>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "ALuaState.h"


namespace tri::lua {
    class ALuaManager {
    public:
        using LuaObject = std::shared_ptr<ALuaState>;
        using LuaRegistry = std::vector<LuaObject>;

        LuaObject CreateLuaEnvironment(const char* EnvName);
    private:
        ALuaManager();
        ~ALuaManager();

        LuaRegistry LuaReg;
    };
}


#endif //ALUAMANAGER_H
