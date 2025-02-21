//
// Created by lepag on 2/21/2025.
//

#ifndef CHILDRENMANAGER_H
#define CHILDRENMANAGER_H
#include <functional>

#include <memory>
#include <string>


namespace tri::ecs::components {
    template<class OwnerBase, class ChildBase>
    class ChildrenManager {
    public:
        using ActorPtr = std::unique_ptr<ChildBase>;
        using Actors = std::vector<ActorPtr>;
        using RawActors = std::vector<ChildBase>;
        enum TraverseType {
            CHILDREN,
            DESCENDANT,
            ANCESTOR
        };

        explicit ChildrenManager(bool childExistOnlyInManager = false) {
            m_deleteChildAfterRemoval = childExistOnlyInManager;
        }
        ~ChildrenManager();

        ChildBase *addChild(ChildBase *child);
        ChildBase *moveChild(OwnerBase *owner, ActorPtr child);
        void removeChild(ChildBase *child);
        void removeAllChildren();

        void traverseHierarchy(TraverseType traverse_type, std::function<bool(ChildBase *)> callback);

        RawActors getChildren(TraverseType traverse_type = CHILDREN);
        int getChildCount();

        void free() const;
    private:
        bool m_deleteChildAfterRemoval = false;
        bool m_destroying = false;
        Actors m_children;
    protected:
        ChildBase* p_moveChild(ActorPtr child);
    };
} // components
// ecs
// tri

#endif //CHILDRENMANAGER_H
