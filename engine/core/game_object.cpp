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

GameObject::GameObject(const char *name, std::initializer_list<Component *> components) : name(name) {
    std::cout << "[" << name << "] Created!" << std::endl;
    transform = std::make_unique<Transform>();
    for (auto item: components) {
        AddComponent(item->name.c_str(), item);
    }
}

GameObject::GameObject(const GameObject &other) {
    name = other.name;
    Transform otherTransform;
    otherTransform.position = other.transform->position;
    otherTransform.size = other.transform->size;
    transform = std::make_unique<Transform>(std::move(otherTransform));
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

void GameObject::AddComponent(const char *id, Component *component) {
    component->transform = transform.get();
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
        component.second->Draw();
    }
}
#pragma endregion