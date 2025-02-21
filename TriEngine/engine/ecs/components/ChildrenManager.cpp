//
// Created by lepag on 2/21/2025.
//

#include "ChildrenManager.h"

#include <algorithm>


namespace tri::ecs::components {
    template<class OwnerBase, class ChildBase>
    ChildrenManager<OwnerBase, ChildBase>::ChildrenManager(bool childExistOnlyInManager) {
        m_deleteChildAfterRemoval = childExistOnlyInManager;
        m_children = {};
    }

    template<class OwnerBase, class ChildBase>
    ChildrenManager<OwnerBase, ChildBase>::~ChildrenManager() {
        removeAllChildren();
    }

    template<class OwnerBase, class ChildBase>
    ChildBase * ChildrenManager<OwnerBase, ChildBase>::addChild(ChildBase *child) {
        ActorPtr actor = std::make_unique<ChildBase>(child);
        m_children.push_back(actor);
        return actor.get();
    }

    template<class OwnerBase, class ChildBase>
    ChildBase *ChildrenManager<OwnerBase, ChildBase>::moveChild(OwnerBase *owner, ActorPtr child) {
        auto* children_manager = dynamic_cast<ChildrenManager*>(owner->children);
        children_manager->p_moveChild(child);
        return child.get();
    }

    template<class OwnerBase, class ChildBase>
    ChildBase *ChildrenManager<OwnerBase, ChildBase>::p_moveChild(ActorPtr child) {
        m_children.push_back(std::move(child));
        return child.get();
    }

    template<class OwnerBase, class ChildBase>
    void ChildrenManager<OwnerBase, ChildBase>::removeChild(ChildBase *child) {
        ActorPtr* childPtr = std::find(m_children.begin(), m_children.end(), child);
        childPtr->release();
    }

    template<class OwnerBase, class ChildBase>
    void ChildrenManager<OwnerBase, ChildBase>::removeAllChildren() {
        traverseHierarchy(CHILDREN, [this](ChildBase *child) {
            removeChild(child);
        });
    }

    template<class OwnerBase, class ChildBase>
    void ChildrenManager<OwnerBase, ChildBase>::traverseHierarchy(TraverseType traverse_type,
        std::function<bool(ChildBase *)> callback) {

        bool exit_early = false;

        std::ranges::for_each(m_children.begin(), m_children.end(), [callback, traverse_type, this, &exit_early](ChildBase *child) {
            if (exit_early) {
                return;
            }
            switch (traverse_type) {
                case CHILDREN:
                    if (!callback(child)) {
                        exit_early = true;
                    }
                    break;
                case DESCENDANT | ANCESTOR:
                   ActorPtr parent = child->getParent();
                    while (parent != nullptr && callback(parent)) {
                        parent = parent->getParent();
                    }
                   break;
            }
        });
    }

    template<class OwnerBase, class ChildBase>
    typename ChildrenManager<OwnerBase, ChildBase>::RawActors ChildrenManager<OwnerBase, ChildBase>::getChildren(TraverseType traverse_type) {
        RawActors children{};
        traverseHierarchy(traverse_type, [&](ChildBase *child) {
            children.push_back(child);
        });
        return children;
    }

    template<class OwnerBase, class ChildBase>
    int ChildrenManager<OwnerBase, ChildBase>::getChildCount() {
        return m_children.size();
    }
} // components
// ecs
// tri