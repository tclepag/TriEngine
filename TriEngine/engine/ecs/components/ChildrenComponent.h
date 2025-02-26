//
// Created by lepag on 2/26/25.
//

#ifndef CHILDRENCOMPONENT_H
#define CHILDRENCOMPONENT_H
#include <functional>
#include <vector>


namespace tri::ecs::components {
    template<class ParentClass, class ChildClass>
    class ChildrenComponent {
    public:
        using TraverseFun = std::function<void(ChildClass*)>;
        using Child = std::unique_ptr<ChildClass>;
        using Children = std::vector<Child>;
        ChildrenComponent();
        ~ChildrenComponent();

        void Add(Child& child);
        void Remove(Child& child);
        void Update();

        void TraverseChildren(Child& child);

        virtual void OnAdd(Child& child);
        virtual void OnRemove(Child& child);
        virtual void OnUpdate(Child& child);
    private:
        Children children{};
    };
} // components
// ecs
// tri

#endif //CHILDRENCOMPONENT_H
