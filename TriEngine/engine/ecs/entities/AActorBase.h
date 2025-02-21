//
// Created by lepag on 2/21/25.
//

#ifndef ACTOR_H
#define ACTOR_H

#include "../components/ChildrenManager.h"

namespace tri::ecs::entities {

class AActorBase {
public:
    components::ChildrenManager<AActorBase, AActorBase> *children;
    std::string name;
    unsigned int id;

    bool visible_in_inspector = true;

    AActorBase();
    ~AActorBase();

    void init();
    void update();
    void render();
    void free();
protected:
    void p_init();
    void p_update();
    void p_render();
};

} // entities
// ecs
// tri

#endif //ACTOR_H
