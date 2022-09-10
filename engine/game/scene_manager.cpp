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
    } catch (YAML::BadFile &ex) {
        std::cout << "[SceneManager] " << ex.what() << std::endl;
    }
}
std::string &SceneManager::NextScene() {
    if (scenes.empty()) return (std::string &) "";
    auto &next = scenes[currentIndex];
    currentIndex = std::clamp(++currentIndex, 0, static_cast<int>(scenes.size() - 1));
    return next;
}
std::string &SceneManager::FirstScene() {
    if (scenes.empty()) return (std::string &) "";
    currentIndex = 0;
    return scenes[currentIndex];
}

std::string &SceneManager::GetSceneByIndex(int index) {
    if (scenes.empty()) return (std::string &) "";
    currentIndex = index;
    return scenes[currentIndex];
}
