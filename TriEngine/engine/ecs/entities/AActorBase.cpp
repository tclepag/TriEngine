//
// Created by TC on 2/21/25.
//

#include "AActorBase.h"



namespace tri::ecs::entities {
    AActorBase::AActorBase() {
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

    int AActorBase::LuaCreate(lua_State *L) {
        return 1;
    }

    int AActorBase::LuaInit(lua_State* L) {
        return 1;
    }

    int AActorBase::LuaUpdate(lua_State* L) {
        return 1;
    }

    int AActorBase::LuaRender(lua_State* L) {
        return 1;
    }

    int AActorBase::LuaFree(lua_State* L) {
        return 1;
    }

    void AActorBase::RegisterLua(const std::function<void(lua::ALuaState::LuaClass LuaClass)>&) {
        lua::ALuaState::LuaClass LuaClass("AActorBase");
        LuaClass.Constructor = LuaInit;
        LuaClass.Destructor = LuaFree;
    }
} // entities
// ecs
// tri