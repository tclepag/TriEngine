//
// Created by lepag on 2/16/2025.
//

#include "Actor.h"

namespace tri {
    Actor::Actor(Actor* parent_actor) {
        name = "Actor";
        parent = parent_actor;
    }

    Actor::~Actor() {
        for (auto& component : m_components) {
            detachComponent(component);
        }
    }

    void Actor::draw() {  m_draw(); }
    void Actor::update() {  m_update(); }
    void Actor::init() {  m_init(); }
    void Actor::start() {  m_start(); }

    void Actor::m_init() {

    }

    void Actor::m_start() {

    }

    void Actor::m_update() {
        for (auto& component : m_components) {
            component->update();
        }
    }

    void Actor::m_draw() {
        for (auto& component : m_components) {
            component->draw();
        }
    }

    void Actor::attachComponent(ActorComponent* component) {
        if (component->actor != this) {
            if (component->actor != nullptr) {
                component->actor->detachComponent(component);
                return;
            }
        } else {
            return;
        }

        m_components.emplace_back(component);
        component->actor = this;

        component->init();
        component->start();
    }

    void Actor::detachComponent(ActorComponent* component) {
        for (auto& c : m_components) {
            if (c == component) {
                m_components.erase(std::ranges::find(m_components, component));
                c->free();
                break;
            }
        }
    }



} // tri