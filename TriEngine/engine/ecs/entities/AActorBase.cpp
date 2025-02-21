//
// Created by lepag on 2/21/25.
//

#include "AActorBase.h"



namespace tri::ecs::entities {
    AActorBase::AActorBase(): id(0) {
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
} // entities
// ecs
// tri