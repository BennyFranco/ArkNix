#include "scene.h"

#include <iostream>

using namespace nim;

void Scene::Init() {
    std::cout << "[Scene] Init" << std::endl;
    sceneData = std::make_unique<SceneData>();
}

void Scene::Update() {
    for (auto gameObject: sceneData->gameObjects) {
        gameObject.Update();
    }
}

void Scene::Quit() {
    std::cout << "[Scene] Quit" << std::endl;
}