//
// Created by lepag on 2/21/25.
//

#ifndef ACTOR_H
#define ACTOR_H

#include "../components/ChildrenManager.h"
#include "../../lua/ALuaEnvironment.h"

namespace tri::ecs::entities {

class AActorBase {
public:
    components::ChildrenManager<AActorBase, AActorBase> *children;
    std::string name;
    unsigned int id;

    bool visible_in_inspector = true;

    AActorBase(lua::ALuaEnvironment* lua_environment);
    ~AActorBase();

    void init();
    void update();
    void render();
    void free();

    void lua_init();
    void lua_update();
    void lua_render();
    void lua_free();

    static AActorBase* lua_create(lua::ALuaEnvironment *lua_environment);

    void luaInit(lua::ALuaEnvironment* lua_environment);
    static void luaRegister(lua::ALuaEnvironment* lua_environment);
protected:
    lua::ALuaEnvironment *luaEnv;
    void p_init();
    void p_update();
    void p_render();
};

} // entities
// ecs
// tri

#endif //ACTOR_H
