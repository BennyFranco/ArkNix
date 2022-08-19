#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "component.h"
#include "entity.h"
#include "sprite_component.h"
#include <initializer_list>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace nim {
    class GameObject : public Entity {
    public:
        GameObject();
        GameObject(const char *name);
        // GameObject(const char *name, std::initializer_list<Component *> components);
        GameObject(const GameObject &other);
        GameObject(GameObject &&other);
        ~GameObject();

        GameObject &operator=(const GameObject &other);
        GameObject &operator=(GameObject &&other);

        virtual void Init() override {}
        virtual void Update() override;
        virtual void Quit() override {}

        void AddComponent(std::shared_ptr<Component> component);
        // Component *GetComponent(const char *id);
        std::vector<std::shared_ptr<Component>> Components() const { return components; }

    public:
        std::string name;
        std::unique_ptr<Transform> transform;

    private:
        std::vector<std::shared_ptr<Component>> components;
    };
}// namespace nim

namespace YAML {
    template<>
    struct convert<nim::GameObject> {
        static YAML::Node encode(const nim::GameObject &go) {
            YAML::Node node;
            node["type"] = "GameObject";
            node["name"] = go.name;
            node["transform"] = go.transform.get();
            for (auto &component: go.Components()) {
                if (component->type == nim::ComponentType::Sprite)
                    node["components"].push_back(dynamic_cast<nim::SpriteComponent *>(component.get()));
                else
                    node["components"].push_back(component.get());
            }
            return node;
        }

        static bool decode(const YAML::Node &node, nim::GameObject &go) {
            // TODO: Verify Type content if exist
            if (!node["type"]) return false;

            go.name = node["name"].as<std::string>();
            auto t = node["transform"].as<nim::Transform>();
            go.transform->size = t.size;
            go.transform->position = t.position;

            if (node["components"].IsSequence()) {
                for (int i = 0; i < node["components"].size(); i++) {
                    if (node["components"][i]["type"].as<int>() == (int) nim::ComponentType::Sprite) {
                        auto sc = std::move(node["components"][i].as<nim::SpriteComponent>());
                        go.AddComponent(std::make_shared<nim::SpriteComponent>(sc));
                    }
                    // TODO: Add logic for other kind of components or generic.
                    // else
                    //     node["components"].push_back(component.get());
                }
            }

            return true;
        }
    };
}// namespace YAML
#endif//GAME_OBJECT_H