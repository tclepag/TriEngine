//
// Created by lepag on 2/16/2025.
//

#include "ActorComponent.h"

namespace tri {
    ActorComponent::ActorComponent() {
        name = typeid(this).name();
    }

    void ActorComponent::init() {
        std::cout << "Hello Component World!" << "ADDED:" << name << std::endl;
    }

    void ActorComponent::start() {
        std::cout << "Hello Component World!" << "STARTED:" << name << std::endl;
    }

    void ActorComponent::draw(core::Screen* from) {

    }

    void ActorComponent::update() {

    }

    void ActorComponent::editor_update() {

    }

    void ActorComponent::free() {
        std::cout << "Goodbye Component World!" << "FREE:" << name << std::endl;
        delete this;
    }

} // tri