#include "scene.h"

#include <fstream>
#include <iostream>
#include <time.h>

using namespace nim;

Scene::Scene() {
    std::cout << "[Scene] Init" << std::endl;
    sceneData = std::make_unique<SceneData>();
}

Scene::Scene(const Scene &otherScene) {
    SceneData data;
    data.name = otherScene.sceneData->name;
    data.gameObjects = otherScene.sceneData->gameObjects;
    sceneData = std::make_unique<SceneData>(data);
}

Scene::Scene(Scene &&otherScene) {
    sceneData = std::move(otherScene.sceneData);
}
Scene::~Scene() {}

Scene &Scene::operator=(const Scene &otherScene) {
    if (this != &otherScene) {
        SceneData *data = new SceneData();
        data->name = otherScene.sceneData->name;
        data->gameObjects = otherScene.sceneData->gameObjects;
        sceneData.reset(data);
    }

    return *this;
}
Scene &Scene::operator=(Scene &&otherScene) {
    if (this != &otherScene)
        sceneData.reset(otherScene.sceneData.release());
    return *this;
}

void Scene::Init() {}

void Scene::Update() {
    for (auto gameObject: sceneData->gameObjects) {
        gameObject.Update();
    }
}

void Scene::Quit() {
    std::cout << "[Scene] Quit" << std::endl;
}

std::unique_ptr<Scene> Scene::LoadScene(std::string sceneName) {
    // TODO: include scenes in asset manager
    YAML::Node sceneNode = YAML::LoadFile(sceneName);
    SceneData sceneData = sceneNode.as<SceneData>();
    auto currentScene = std::make_unique<Scene>();
    currentScene->GetData()->name = std::move(sceneData.name);
    currentScene->GetData()->gameObjects = std::move(sceneData.gameObjects);
    return currentScene;
}

void Scene::Save(std::string filename) {
    if (filename.empty()) filename = this->Name() + std::string(".yaml");

    time_t now;
    time(&now);

    YAML::Node common;
    common["version"] = fileVersion;

    YAML::Emitter document;
    document << YAML::Comment("Scene: " + this->Name());
    document << YAML::Newline;
    document << YAML::Comment("Date: " + std::string(ctime(&now)));
    document << YAML::BeginDoc;
    document << YAML::convert<SceneData>::encode(*sceneData.get());
    document << common;
    document << YAML::EndDoc;

    std::ofstream fileOut(filename);
    fileOut << document.c_str();
    fileOut.close();
}