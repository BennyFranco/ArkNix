#include "game_object.h"
#include "game.h"
#include <iostream>
#include <memory>
#include <thread>
#include <utility>

using namespace nim;

GameObject::GameObject() : name("GameObject"), isDirty(false) {
    transform = std::make_unique<Transform>();
    collisionLayer = Layer::None;
}

GameObject::GameObject(std::string goName) : name(std::move(goName)), isDirty(false) {
    transform = std::make_unique<Transform>();
    collisionLayer = Layer::None;
}

GameObject::GameObject(std::string goName, Transform transform) : name(std::move(goName)), isDirty(false) {
    this->transform = std::make_unique<Transform>(std::move(transform));
    collisionLayer = Layer::None;
}

GameObject::GameObject(const GameObject &other) {
    name = other.name;
    transform = other.transform;
    components = other.components;
    collisionLayer = other.collisionLayer;
    isDirty = other.isDirty;
}

GameObject::GameObject(GameObject &&other) noexcept {
    name = std::move(other.name);
    transform = std::move(other.transform);
    components = std::move(other.components);
    collisionLayer = other.collisionLayer;
    isDirty = other.isDirty;

    other.collisionLayer = Layer::None;
}

GameObject::~GameObject() {
    components.clear();
}

GameObject &GameObject::operator=(const GameObject &other) {
    if (&other != this) {
        components.clear();
        name = other.name;
        transform = std::make_shared<Transform>(*other.transform);
        components = other.components;
        collisionLayer = other.collisionLayer;
        isDirty = other.isDirty;
    }
    return *this;
}

GameObject &GameObject::operator=(GameObject &&other) noexcept {
    if (&other != this) {
        transform = nullptr;
        components.clear();

        name = std::move(other.name);
        transform = std::move(other.transform);
        components = std::move(other.components);
        collisionLayer = other.collisionLayer;
        isDirty = other.isDirty;

        other.collisionLayer = Layer::None;
    }
    return *this;
}

void GameObject::AddComponent(std::shared_ptr<Component> component) {
    component->SetTransform(transform.get());
    components.emplace_back(std::move(component));
}

GameObject *GameObject::Instantiate(std::string goName, Transform transform, std::shared_ptr<Component> component) {
    GameObject newGo(std::move(goName), std::move(transform));
    newGo.AddComponent(std::move(component));
    return Game::AddGameObject(std::move(newGo));
}

GameObject *GameObject::Instantiate(std::string goName, Transform transform,
                                    std::initializer_list<std::shared_ptr<Component>> newComponents) {
    GameObject newGo(std::move(goName), std::move(transform));
    for (const auto &component: newComponents)
        newGo.AddComponent(component);
    return Game::AddGameObject(std::move(newGo));
}

GameObject *GameObject::Instantiate(GameObject &&go) {
    return Game::AddGameObject(std::move(go));
}

void GameObject::Destroy(const GameObject *go) {
    Game::RemoveGameObject(go->name);
}

void GameObject::Destroy(const GameObject *go, const uint msToDestroyIt) {
    auto goName = go->name;
    std::thread programDestroyInvocation([goName, msToDestroyIt]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(msToDestroyIt));
        Game::RemoveGameObject(goName);
    });
    programDestroyInvocation.detach();
}

#pragma region entity_functions
void GameObject::Init() {
    // I want to be sure that all components have access to parent,
    // before call Init.
    for (auto &component: components) {
        component->Setup(this);
    }

    for (auto &component: components) {
        component->Init();
    }
}

void GameObject::Update() {
    for (auto &component: components) {
        component->Update();
    }
}

void GameObject::Quit() {
    for (auto &component: components) {
        component->Quit();
    }
}
#pragma endregion

void GameObject::OnCollisionEnter(const GameObject &other) const {
    for (const auto &component: components) {
        component->OnCollisionEnter(other);
    }
}