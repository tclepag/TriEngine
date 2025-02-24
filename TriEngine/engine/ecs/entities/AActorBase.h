//
// Created by lepag on 2/21/25.
//

#ifndef ACTOR_H
#define ACTOR_H

#include <string>

#include "../../lua/ALuaManager.h"

namespace tri::ecs::entities {

class AActorBase {
public:

    std::string Name;
    unsigned int Id;

    bool bVisibleInInspector = true;

    AActorBase();
    ~AActorBase();

    void Init();
    void Update();
    void Render();
    void Free();

    static int LuaCreate(lua_State *L);
    static int LuaInit(lua_State* L);
    static int LuaUpdate(lua_State* L);
    static int LuaRender(lua_State* L);
    static int LuaFree(lua_State* L);

    static void RegisterLua(const std::function<void(lua::ALuaState::LuaClass LuaClass)>&);
};

} // entities
// ecs
// tri

#endif //ACTOR_H
