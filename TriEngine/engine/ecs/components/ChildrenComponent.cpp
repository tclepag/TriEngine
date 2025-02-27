//
// Created by lepag on 2/26/25.
//

#include "ChildrenComponent.h"



namespace tri::ecs::components {
    template<class ParentClass, class ChildClass>
    ChildrenComponent<ParentClass, ChildClass>::ChildrenComponent() {
    }

    template<class ParentClass, class ChildClass>
    ChildrenComponent<ParentClass, ChildClass>::~ChildrenComponent() {
    }

    template<class ParentClass, class ChildClass>
    void ChildrenComponent<ParentClass, ChildClass>::Add(ChildClass &child) {
        auto* Children = child.Children;
        if (Children != nullptr) {
            Children->TransferToParent(this->Parent, child);
        } else {
            children.push_back(std::make_unique<ChildClass>(child));
        }
    }

    template<class ParentClass, class ChildClass>
    void ChildrenComponent<ParentClass, ChildClass>::Remove(ChildClass &child) {
    }

    template<class ParentClass, class ChildClass>
    void ChildrenComponent<ParentClass, ChildClass>::RemoveAll() {
    }

    template<class ParentClass, class ChildClass>
    void ChildrenComponent<ParentClass, ChildClass>::Update() {
    }

    template<class ParentClass, class ChildClass>
    void ChildrenComponent<ParentClass, ChildClass>::TraverseChildren(TraverseFun traverse_fun) {
    }

    template<class ParentClass, class ChildClass>
    void ChildrenComponent<ParentClass, ChildClass>::TraverseDescendants(TraverseFun traverse_fun) {
    }

    template<class ParentClass, class ChildClass>
    void ChildrenComponent<ParentClass, ChildClass>::TraverseAncestors(TraverseFun traverse_fun) {
    }

    template<class ParentClass, class ChildClass>
    void ChildrenComponent<ParentClass, ChildClass>::OnAdd(Child child) {
    }

    template<class ParentClass, class ChildClass>
    void ChildrenComponent<ParentClass, ChildClass>::OnRemove(Child child) {
    }

    template<class ParentClass, class ChildClass>
    void ChildrenComponent<ParentClass, ChildClass>::OnUpdate(Child child) {
    }

    template<class ParentClass, class ChildClass>
    void ChildrenComponent<ParentClass, ChildClass>::TransferToParent(ParentClass *parent, Child child) {
    }

    template<class ParentClass, class ChildClass>
    void ChildrenComponent<ParentClass, ChildClass>::OnTransfer(Child child) {
    }
} // components
// ecs
// tri