#ifndef COMPONENT_H
#define COMPONENT_H

#include "transform.h"
#include <string>

namespace nim {
    class Component {
    public:
        virtual void Draw(){};

    public:
        std::string name;
        Transform *transform;
    };
}// namespace nim
#endif// COMPONENT_H