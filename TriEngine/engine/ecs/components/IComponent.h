//
// Created by lepag on 2/26/2025.
//

#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <string>

namespace tri::ecs::components {

class IComponent {
public:
    std::string Name;
    virtual ~IComponent() = default;
    virtual void Update() = 0;
    virtual void Render() = 0;
};

} // components
// ecs
// tri

#endif //ICOMPONENT_H
