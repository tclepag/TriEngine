//
// Created by lepag on 2/16/2025.
//

#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <glad/glad.h>
#include "../core/Screen.h"

#include "components/ActorComponent.h"

namespace tri {
class Actor {
    public:
    std::string name;
    Actor* parent;

      Actor(Actor* parent_actor);

    virtual ~Actor();

    virtual void init(); // When the actor loads into the world
    virtual void start(); // When the actor is fully loaded into the world
    virtual void update(); // When the world updates
    virtual void draw(core::Screen* from); // When the world is drawn


    void attachComponent(ActorComponent* component); // Add a component to this actor
    void detachComponent(ActorComponent* component); // Remove a component from this actor
private:
    void m_init();
    void m_start();
    void m_update();
    void m_draw(core::Screen* from) const;
protected:
    std::vector<ActorComponent*> m_components;
};

} // tri

#endif //ACTOR_HPP
