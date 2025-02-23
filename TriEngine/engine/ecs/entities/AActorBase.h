//
// Created by lepag on 2/21/25.
//

#ifndef ACTOR_H
#define ACTOR_H

#include "../components/ChildrenManager.h"

namespace tri::ecs::entities {

class AActorBase {
public:
    components::ChildrenManager<AActorBase, AActorBase> *Children;
    std::string Name;
    unsigned int Id;

    bool bVisibleInInspector = true;

    AActorBase(lua::ALuaEnvironment* lua_environment);
    ~AActorBase();

    void Init();
    void Update();
    void Render();
    void Free();

    void LuaInit();
    void LuaUpdate();
    void LuaRender();
    void LuaFree();

    static AActorBase* LuaNew(lua::ALuaEnvironment *lua_environment);
protected:
    lua::ALuaEnvironment *bLuaEnv;
};

} // entities
// ecs
// tri

#endif //ACTOR_H
