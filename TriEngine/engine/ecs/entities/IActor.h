//
// Created by lepag on 2/26/2025.
//

#ifndef IACTOR_H
#define IACTOR_H



namespace tri::ecs::entities {

class IActor {
public:
    virtual ~IActor() = default;

    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;


};

} // entities
// ecs
// tri

#endif //IACTOR_H
