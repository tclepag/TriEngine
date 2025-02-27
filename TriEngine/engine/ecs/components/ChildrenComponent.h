//
// Created by lepag on 2/26/25.
//

#ifndef CHILDRENCOMPONENT_H
#define CHILDRENCOMPONENT_H

#include <functional>
#include <memory>
#include <vector>
#include "IComponent.h"

namespace tri::ecs::components {
    template<class ParentClass, class ChildClass>
    class ChildrenComponent : public IComponent {
    public:
        using TraverseFun = std::function<void(ChildClass*)>;
        using Child = std::unique_ptr<ChildClass>;
        using Children = std::vector<Child>;
        ChildrenComponent();
        ~ChildrenComponent() override;

        void Add(ChildClass& child);
        void Remove(ChildClass& child);
        void RemoveAll();
        void Update() override;

        void TraverseChildren(TraverseFun traverse_fun);
        void TraverseDescendants(TraverseFun traverse_fun);
        void TraverseAncestors(TraverseFun traverse_fun);

        virtual void OnAdd(Child child);
        virtual void OnRemove(Child child);
        virtual void OnUpdate(Child child);
    private:
        Children children{};
    protected:
        void TransferToParent(ParentClass* parent, Child child);
        void OnTransfer(Child child);
    };
} // components
// ecs
// tri

#endif //CHILDRENCOMPONENT_H
