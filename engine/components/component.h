#ifndef COMPONENT_H
#define COMPONENT_H

#include "transform.h"
#include <string>

namespace nim {
    class Component {
    public:
        virtual ~Component() = default;
        virtual void Init(){};
        virtual void Update(){};
        virtual void Quit(){};
        virtual Transform *GetTransform() const { return transform; };
        virtual void SetTransform(Transform *transform) {
            this->transform = transform;
        };

    public:
        std::string name;

    protected:
        Transform *transform;// owned by Parent GameObject
    };
}// namespace nim
#endif// COMPONENT_H