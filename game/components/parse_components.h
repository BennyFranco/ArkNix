#ifndef PARSE_COMPONENTS_H
#define PARSE_COMPONENTS_H
#include "parser.h"

namespace nim {
    static void DeserializeCustomComponent(std::string goName, GameObject &go, const YAML::Node &node) {
        if (goName == "DebugComponent") {
            go.AddComponent(std::make_shared<nim::DebugComponent>());
        }
    }
    static void RegisterCustomComponents() {
        CustomComponentHelper::Instance().DeserializeCustom.AddListener(DeserializeCustomComponent);
    }
}// namespace nim

#endif//PARSE_COMPONENTS_H