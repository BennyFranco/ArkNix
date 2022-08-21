#include "game_object.h"
#include <iostream>

using namespace nim;

GameObject::GameObject() : name("GameObject") {
    std::cout << "[" << name << "] Created!" << std::endl;
    transform = std::make_unique<Transform>();
}

GameObject::GameObject(const char *name) : name(name) {
    std::cout << "[" << name << "] Created!" << std::endl;
    transform = std::make_unique<Transform>();
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