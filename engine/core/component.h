#ifndef COMPONENT_H
#define COMPONENT_H

#include "transform.h"
#include <string>

namespace nim {
    class Component : public Transform {
    public:
        virtual void Draw(){};
        std::string name;
    };
}// namespace nim
#endif// COMPONENT_H