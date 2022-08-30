#ifndef COMPONENT_H
#define COMPONENT_H

#include "transform.h"
#include "types.h"
#include <string>

namespace nim {
    class GameObject;
    class Component {
    public:
        virtual ~Component() = default;
        virtual void Init(){};
        virtual void Update(){};
        virtual void Quit(){};
        virtual void OnCollisionEnter(const GameObject &other){};
        virtual Transform *GetTransform() const { return transform; };
        virtual void SetTransform(Transform *transform) { this->transform = transform; };
        void Setup(GameObject *parent) { this->parent = parent; };
        void SetParent(GameObject *parent) { this->parent = parent; }

    public:
        std::string name;
        GameObject *parent;

    protected:
        Transform *transform;// owned by Parent GameObject
    };
}// namespace nim
#endif// COMPONENT_H