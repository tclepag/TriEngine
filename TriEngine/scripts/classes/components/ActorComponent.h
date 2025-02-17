//
// Created by lepag on 2/16/2025.
//

#ifndef ACTORCOMPONENT_HPP
#define ACTORCOMPONENT_HPP

#include <iostream>
#include <typeinfo>

namespace tri {
    class Actor;
class ActorComponent {
public:
    std::string name;
    Actor* actor;

    explicit ActorComponent();

    virtual ~ActorComponent() = default;

    virtual void init(); // When the component loads
    virtual void start(); // When the component loads and is ready
    virtual void update(); // Updates during runtime
    virtual void draw();
    virtual void editor_update(); // Updates in the editor

    void free();
};

} // tri

#endif //ACTORCOMPONENT_HPP
