//
// Created by lepag on 2/24/25.
//

#ifndef ALUAMANAGER_H
#define ALUAMANAGER_H
#include <memory>
#include <vector>

#include <sol/sol.hpp>


namespace tri::lua {
    class ALuaManager {
    public:
        using LuaObject = std::shared_ptr<sol::state>;
        using LuaRegistry = std::unordered_map<const char*, LuaObject>;
        using LuaCallback = std::function<void(LuaObject LuaObject)>;

        static ALuaManager& Instance();

        ALuaManager(const ALuaManager&) = delete;
        ALuaManager& operator=(const ALuaManager&) = delete;

        LuaObject CreateLuaEnvironment(const char* EnvName, const LuaCallback& Callback);
        void RunAllEnvironments(const LuaCallback& Callback);
    private:
        ALuaManager();
        ~ALuaManager();

        LuaRegistry LuaReg;
    };
}


#endif //ALUAMANAGER_H
