#ifndef PARSE_COMPONENTS_H
#define PARSE_COMPONENTS_H
#include "bullet_controller.h"
#include "debug_component.h"
#include "enemies_manager.h"
#include "parser.h"
#include "player_controller.h"
#include "selection_cursor.h"

namespace nim {
    static void DeserializeCustomComponent(std::string goName, GameObject &go, const YAML::Node &node) {
        if (goName == "DebugComponent") {
            go.AddComponent(std::make_shared<nim::DebugComponent>());
        } else if (goName == "PlayerController") {
            auto playerController = std::move(node.as<galaga::PlayerController>());
            go.AddComponent(std::make_shared<galaga::PlayerController>(playerController));
        } else if (goName == "BulletController") {
            go.AddComponent(std::make_shared<galaga::BulletController>());
        } else if (goName == "EnemiesManager") {
            auto component = std::move(node.as<galaga::EnemiesManager>());
            go.AddComponent(std::make_shared<galaga::EnemiesManager>(component));
        } else if (goName == "SelectionCursor") {
            auto component = std::move(node.as<galaga::SelectionCursor>());
            go.AddComponent(std::make_shared<galaga::SelectionCursor>(component));
        }
    }
    static void RegisterCustomComponents() {
        CustomComponentHelper::Instance().DeserializeCustom.AddListener(DeserializeCustomComponent);
    }
}// namespace nim

#endif//PARSE_COMPONENTS_H