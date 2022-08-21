#ifndef COMPONENT_H
#define COMPONENT_H

#include "transform.h"
#include "yaml-cpp/yaml.h"
#include <string>

namespace nim {
    enum class ComponentType {
        Generic = 0,
        Sprite,
        Controller,
        Custom
    };

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
        ComponentType type;

    protected:
        Transform *transform;// owned by Parent GameObject
    };
}// namespace nim

namespace YAML {
    template<>
    struct convert<nim::ComponentType> {
        static Node encode(const nim::ComponentType &rhs) { return Node((int) rhs); }

        static bool decode(const Node &node, nim::ComponentType &rhs) {
            if (!node.IsScalar()) return false;
            rhs = static_cast<nim::ComponentType>(node.as<int>());
            return true;
        }
    };
}// namespace YAML
#endif// COMPONENT_H