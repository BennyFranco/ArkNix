#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Quit() = 0;
};

#endif//ENTITY_H