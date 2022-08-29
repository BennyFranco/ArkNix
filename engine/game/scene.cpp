#include "scene.h"

#include <fstream>
#include <iostream>
#include <mutex>
#include <time.h>

using namespace nim;

Scene::Scene() {
    std::cout << "[Scene] Constructed" << std::endl;
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

void Scene::Init() {
    std::cout << "[Scene] Init" << std::endl;
    for (auto gameObject: sceneData->gameObjects) {
        gameObject.Init();
    }
}

void Scene::Update() {
    for (auto gameObject: sceneData->gameObjects) {
        gameObject.Update();
    }
}

void Scene::Quit() {
    std::cout << "[Scene] Quit" << std::endl;
    for (auto gameObject: sceneData->gameObjects) {
        gameObject.Quit();
    }
}

GameObject *Scene::AddGameObject(GameObject &&gameObject) {
    sceneData->gameObjects.emplace_back(std::move(gameObject));
    auto lastGo = &sceneData->gameObjects.back();
    lastGo->Init();
    return lastGo;
}

void Scene::RemoveGameObject(const std::string name) {
    std::unique_lock<std::mutex> lck(mtx);
    mtxCondition.wait(lck, [this] { return this->canDelete; });
    canDelete = false;
    for (auto it = sceneData->gameObjects.begin(); it != sceneData->gameObjects.end(); it++) {
        if (name == it->name) {
            sceneData->gameObjects.erase(it);
            break;
        }
    }
    canDelete = true;
}

std::unique_ptr<Scene> Scene::LoadScene(std::string sceneName) {
    try {
        YAML::Node sceneNode = YAML::LoadFile(kScenesPath + sceneName);
        SceneData sceneData = sceneNode.as<SceneData>();
        auto currentScene = std::make_unique<Scene>();
        currentScene->GetData()->name = std::move(sceneData.name);
        currentScene->GetData()->gameObjects = std::move(sceneData.gameObjects);
        return currentScene;
    } catch (YAML::BadFile ex) {
        std::cout << "[Scene] " << ex.what() << std::endl;
    }
    return nullptr;
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

    std::ofstream fileOut(kScenesPath + filename);
    fileOut << document.c_str();
    fileOut.close();
}