#ifndef COMPONENT_H
#define COMPONENT_H

#include "transform.h"
#include "yaml-cpp/yaml.h"
#include <string>

namespace nim {
    enum class ComponentType {
        Generic = 0,
        Sprite,
        Unknown
    };

    class Component {
    public:
        virtual ~Component() = default;
        virtual void Draw(){};
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
    struct convert<nim::Component> {
        static YAML::Node encode(const nim::Component &component) {
            YAML::Node node;
            node["name"] = component.name;
            return node;
        }

        static bool decode(const YAML::Node &node, nim::Component &component) {
            if (!node["name"]) return false;
            component.name = node["name"].as<std::string>();
            return true;
        }
    };

    template<>
    struct convert<nim::Component *> {
        static YAML::Node encode(const nim::Component *component) {
            YAML::Node node;
            node["name"] = component->name;
            return node;
        }

        static bool decode(const YAML::Node &node, nim::Component &component) {
            if (!node["name"]) return false;
            component.name = node["name"].as<std::string>();
            return true;
        }
    };
}// namespace YAML
#endif// COMPONENT_H