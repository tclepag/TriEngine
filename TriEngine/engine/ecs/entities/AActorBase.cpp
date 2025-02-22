//
// Created by lepag on 2/21/25.
//

#include "AActorBase.h"



namespace tri::ecs::entities {
    AActorBase::AActorBase(lua::ALuaEnvironment* lua_environment): id(0), luaEnv(lua_environment) {
        children = new components::ChildrenManager<AActorBase, AActorBase>(false);
    }

    AActorBase::~AActorBase() {
    }

    void AActorBase::init() {
    }

    void AActorBase::update() {
    }

    void AActorBase::render() {
    }

    void AActorBase::free() {
    }

    void AActorBase::p_init() {
        init();
    }

    void AActorBase::p_update() {
        update();
    }

    void AActorBase::p_render() {
        render();
    }

    AActorBase *AActorBase::lua_create(lua::ALuaEnvironment *lua_environment) {
        auto* self = new AActorBase(lua_environment);
        lua_pushlightuserdata(lua_environment->getLuaState(), self);

        self->luaInit(lua_environment);

        luaL_getmetatable(lua_environment->getLuaState(), "Actor");
        lua_setmetatable(lua_environment->getLuaState(), -2);

        return self;
    }


    void AActorBase::luaInit(lua::ALuaEnvironment *lua_environment) {

    }

    void AActorBase::luaRegister(lua::ALuaEnvironment *lua_environment) {
        lua_environment->newLuaClass("Actor");

        lua_environment->luaSet<AActorBase*>(std::function(lua_create));
        lua_environment->luaSet("new");
        lua_environment->setLuaTable(-3);
    }


} // entities
// ecs
// tri