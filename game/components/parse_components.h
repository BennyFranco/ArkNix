#ifndef PARSE_COMPONENTS_H
#define PARSE_COMPONENTS_H
#include "debug_component.h"
#include "parser.h"
#include "player_controller.h"

namespace nim {
    static void DeserializeCustomComponent(std::string goName, GameObject &go, const YAML::Node &node) {
        if (goName == "DebugComponent") {
            go.AddComponent(std::make_shared<nim::DebugComponent>());
        } else if (goName == "PlayerController") {
            auto playerController = std::move(node.as<galaga::PlayerController>());
            go.AddComponent(std::make_shared<galaga::PlayerController>(playerController));
        }
    }
    static void RegisterCustomComponents() {
        CustomComponentHelper::Instance().DeserializeCustom.AddListener(DeserializeCustomComponent);
    }
}// namespace nim

#endif//PARSE_COMPONENTS_H