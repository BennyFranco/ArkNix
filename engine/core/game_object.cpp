#include "game_object.h"
#include <iostream>

using namespace nim;

GameObject::GameObject() : name("GameObject") {
    std::cout << "[" << name << "] Created!" << std::endl;
}

GameObject::GameObject(const char *name) : name(name) {
    std::cout << "[" << name << "] Created!" << std::endl;
}

GameObject::GameObject(const char *name, std::initializer_list<Component *> components) : name(name) {
    std::cout << "[" << name << "] Created!" << std::endl;
    for (auto item: components) {
        AddComponent(item->name.c_str(), item);
    }
}

void GameObject::AddComponent(const char *id, Component *component) {
    components.emplace(id, component);
}

Component *GameObject::GetComponent(const char *id) {
    if (components.find(id) == components.end()) {
        std::cout << "[" << name << "] Component '" << id << "' doesn't exist!" << std::endl;
        return nullptr;
    }

    return components[id];
}

#pragma region entity_functions
void GameObject::Update() {
    for (auto component: components) {
        component.second->Size(&size);
        component.second->Position(&position);
        component.second->Draw();
    }
}
#pragma endregion