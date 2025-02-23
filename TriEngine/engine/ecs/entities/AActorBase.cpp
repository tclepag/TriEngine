//
// Created by lepag on 2/21/25.
//

#include "AActorBase.h"



namespace tri::ecs::entities {
    AActorBase::AActorBase(lua::ALuaEnvironment* lua_environment): Id(0), bLuaEnv(lua_environment) {
        Children = new components::ChildrenManager<AActorBase, AActorBase>(false);
    }

    AActorBase::~AActorBase() {
    }

    void AActorBase::Init() {
    }

    void AActorBase::Update() {
    }

    void AActorBase::Render() {
    }

    void AActorBase::Free() {
    }

    AActorBase *AActorBase::LuaNew(lua::ALuaEnvironment *lua_environment) {

    }

    luaL_Reg AActorBase::LuaMethods() {

    }

    luaL_Reg AActorBase::LuaMeta() {
        return {
            {"__index", }
        };
    }

} // entities
// ecs
// tri