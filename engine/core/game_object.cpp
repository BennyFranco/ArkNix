#include "game_object.h"
#include "game.h"
#include <future>
#include <iostream>
#include <thread>

using namespace nim;

GameObject::GameObject() : name("GameObject") {
    std::cout << "[" << name << "] Created!" << std::endl;
    transform = std::make_unique<Transform>();
}

GameObject::GameObject(std::string name) : name(name) {
    std::cout << "[" << name << "] Created!" << std::endl;
    transform = std::make_unique<Transform>();
}

GameObject::GameObject(std::string name, Transform transform) : name(name) {
    this->transform = std::make_unique<Transform>(transform);
}

// GameObject::GameObject(const char *name, std::initializer_list<Component *> components) : name(name) {
//     std::cout << "[" << name << "] Created!" << std::endl;
//     transform = std::make_unique<Transform>();
//     for (auto item: components) {
//         AddComponent(item->name.c_str(), item);
//     }
// }

GameObject::GameObject(const GameObject &other) {
    name = other.name;
    transform = other.transform;
    components = other.components;
}

GameObject::GameObject(GameObject &&other) {
    name = std::move(other.name);
    transform = std::move(other.transform);
    components = std::move(other.components);
}

GameObject::~GameObject() {
    components.clear();
}

GameObject &GameObject::operator=(const GameObject &other) {
    if (&other != this) {
        components.clear();
        name = other.name;
        transform.reset(new Transform(*other.transform.get()));
        components = other.components;
    }
    return *this;
}

GameObject &GameObject::operator=(GameObject &&other) {
    if (&other != this) {
        name = nullptr;
        transform = nullptr;
        components.clear();

        name = std::move(other.name);
        transform = std::move(other.transform);
        components = std::move(other.components);
    }
    return *this;
}

void GameObject::AddComponent(std::shared_ptr<Component> component) {
    component->SetTransform(transform.get());
    components.emplace_back(component);
}

GameObject *GameObject::Instantiate(std::string name, Transform transform, std::shared_ptr<Component> component) {
    GameObject newGo(name, transform);
    newGo.AddComponent(component);
    return Game::currentScene->AddGameObject(std::move(newGo));
}

void GameObject::Destroy(const GameObject *go) {
    Game::currentScene->RemoveGameObject(go);
}

void GameObject::Destroy(const GameObject *go, const uint msToDestroyIt) {
    std::thread programDestroyInvocation([go, msToDestroyIt]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(msToDestroyIt));
        Game::currentScene->RemoveGameObject(go);
    });
    programDestroyInvocation.detach();
}

// Component *GameObject::GetComponent(const char *id) {
//     if (components.find(id) == components.end()) {
//         std::cout << "[" << name << "] Component '" << id << "' doesn't exist!" << std::endl;
//         return nullptr;
//     }

//     return components[id].get();
// }

#pragma region entity_functions
void GameObject::Init() {
    for (int i = 0; i < components.size(); i++) {
        components[i]->Init();
    }
}

void GameObject::Update() {
    for (int i = 0; i < components.size(); i++) {
        components[i]->Update();
    }
}

void GameObject::Quit() {
    for (int i = 0; i < components.size(); i++) {
        components[i]->Quit();
    }
}
#pragma endregion