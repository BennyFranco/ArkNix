#include "scene.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <utility>

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

Scene::Scene(Scene &&otherScene) noexcept {
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
Scene &Scene::operator=(Scene &&otherScene) noexcept {
    if (this != &otherScene)
        sceneData = std::move(otherScene.sceneData);
    return *this;
}

void Scene::Init() {
    std::cout << "[Scene] Init" << std::endl;
    for (auto gameObject: sceneData->gameObjects) {
        gameObject.Init();
    }
}

void Scene::Update() {
    for (auto &gameObject: sceneData->gameObjects) {
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

void Scene::RemoveGameObject(const std::string &name) {
    std::unique_lock<std::mutex> lck(mtx);
    mtxCondition.wait(lck, [this] { return this->canDelete; });
    canDelete = false;
    for (auto &gameObject: sceneData->gameObjects) {
        if (name == gameObject.name) {
            gameObject.SetDirty();
            break;
        }
    }
    canDelete = true;
}

void Scene::RemoveDirtyObjects() {
    for (auto it = sceneData->gameObjects.begin(); it != sceneData->gameObjects.end(); it++) {
        if (it->IsDirty()) {
            it->Quit();
            it = sceneData->gameObjects.erase(it);

            if (it == sceneData->gameObjects.end()) break;
        }
    }
}

std::unique_ptr<Scene> Scene::LoadScene(const std::string &sceneName) {
    try {
        YAML::Node sceneNode = YAML::LoadFile(kScenesPath + sceneName);
        auto sceneData = sceneNode.as<SceneData>();
        auto currentScene = std::make_unique<Scene>();
        currentScene->GetData()->name = std::move(sceneData.name);
        currentScene->GetData()->gameObjects.clear();
        currentScene->GetData()->gameObjects = std::move(sceneData.gameObjects);
        return currentScene;
    } catch (YAML::BadFile &ex) {
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
    document << YAML::convert<SceneData>::encode(*sceneData);
    document << common;
    document << YAML::EndDoc;

    std::ofstream fileOut(kScenesPath + filename);
    fileOut << document.c_str();
    fileOut.close();
}