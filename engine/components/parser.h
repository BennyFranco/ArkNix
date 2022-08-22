#ifndef PARSER_H
#define PARSER_H

#include "animation_component.h"
#include "character_controller.h"
#include "debug_component.h"
#include "game_object.h"
#include "sprite_component.h"

namespace YAML {
    template<>
    struct convert<nim::GameObject> {
        static YAML::Node encode(const nim::GameObject &go) {
            YAML::Node node;
            node["type"] = "GameObject";
            node["name"] = go.name;
            node["transform"] = go.transform.get();
            for (auto &component: go.Components()) {
                switch (component->type) {
                    case nim::ComponentType::Sprite: {
                        node["components"].push_back(dynamic_cast<nim::SpriteComponent *>(component.get()));
                    } break;
                    case nim::ComponentType::Controller: {
                        node["components"].push_back(dynamic_cast<nim::CharacterController *>(component.get()));
                    } break;
                    case nim::ComponentType::Animation: {
                        node["components"].push_back(dynamic_cast<nim::AnimationComponent *>(component.get()));
                    } break;
                    case nim::ComponentType::Custom:
                        // TODO: open for custom components from game implementation side. As C++ doesn't have reflection,
                        // I'll handled that feature later, it's out of my current scope.

                    default:
                        break;
                }
            }
            return node;
        }

        static bool decode(const YAML::Node &node, nim::GameObject &go) {
            if (!node["type"]) return false;

            go.name = node["name"].as<std::string>();
            nim::Transform t = node["transform"].as<nim::Transform>();
            go.transform->size = t.size;
            go.transform->position = t.position;

            if (node["components"].IsSequence()) {
                for (int i = 0; i < node["components"].size(); i++) {
                    switch (node["components"][i]["type"].as<nim::ComponentType>()) {
                        case nim::ComponentType::Sprite: {
                            go.AddComponent(std::make_shared<nim::SpriteComponent>(node["components"][i].as<nim::SpriteComponent>()));
                        } break;
                        case nim::ComponentType::Controller: {
                            auto sc = std::move(node["components"][i].as<nim::CharacterController>());
                            go.AddComponent(std::make_shared<nim::CharacterController>(sc));
                        } break;
                        case nim::ComponentType::Animation: {
                            go.AddComponent(std::make_shared<nim::AnimationComponent>(node["components"][i].as<nim::AnimationComponent>()));
                        } break;
                        case nim::ComponentType::Custom:
                            go.AddComponent(std::make_shared<nim::DebugComponent>());
                        default:
                            break;
                    }
                }
            }

            return true;
        }
    };
}// namespace YAML
#endif