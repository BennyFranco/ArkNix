#include "scene_manager.h"
#include "yaml-cpp/exceptions.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include <algorithm>
#include <iostream>

using namespace nim;

std::string SceneManager::kScenesOrder = "scenes.yaml";
std::string SceneManager::kConfigPath = "../config/";

std::vector<std::string> SceneManager::scenes;
int SceneManager::currentIndex = 0;

void SceneManager::LoadSceneOrder() {
    try {
        YAML::Node sceneOrder = YAML::LoadFile(kConfigPath + kScenesOrder);
        scenes = sceneOrder["order"].as<std::vector<std::string>>();
    } catch (YAML::BadFile& ex) {
        std::cout << "[SceneManager] " << ex.what() << std::endl;
    }
}
std::string &SceneManager::NextScene() {
    auto &next = scenes[currentIndex];
    currentIndex = std::clamp(++currentIndex, 0, static_cast<int>(scenes.size() - 1));
    return next;
}
