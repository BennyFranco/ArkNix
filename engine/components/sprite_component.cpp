#include "sprite_component.h"
#include "asset_manager.h"

using namespace nim;

SpriteComponent::SpriteComponent() : sprite(nullptr) {
    name = "SpriteComponent";
    transform = nullptr;
    type = ComponentType::Sprite;
}

SpriteComponent::SpriteComponent(const char *assetName) {
    name = "SpriteComponent";
    transform = nullptr;
    sprite = nim::AssetManager::Instance().Get<nim::Sprite>(assetName);
    type = ComponentType::Sprite;
}
SpriteComponent::SpriteComponent(const SpriteComponent &other) {
    std::cout << "[SpriteComponent] Copy Constructor"
              << "\n";
    name = other.name;
    transform = other.transform;
    sprite = other.sprite;
    type = other.type;
}
SpriteComponent::SpriteComponent(SpriteComponent &&other) {
    std::cout << "[SpriteComponent] Move Constructor"
              << "\n";
    name = other.name;
    type = other.type;

    transform = other.transform;
    sprite = other.sprite;

    other.transform = nullptr;
    other.sprite = nullptr;
}

SpriteComponent::~SpriteComponent() {
    // delete transform;
    // delete sprite;
    transform = nullptr;
    sprite = nullptr;
}

SpriteComponent &SpriteComponent::operator=(const SpriteComponent &other) {
    std::cout << "[SpriteComponent] Copy operator"
              << "\n";
    if (&other != this) {
        // delete transform;
        // delete sprite;

        transform = nullptr;
        sprite = nullptr;

        name = other.name;
        transform = other.transform;
        sprite = other.sprite;
        type = other.type;
    }

    return *this;
}
SpriteComponent &SpriteComponent::operator=(SpriteComponent &&other) {
    std::cout << "[SpriteComponent] Move operator"
              << "\n";
    if (&other != this) {
        // delete transform;

        // delete sprite;

        transform = nullptr;
        sprite = nullptr;

        name = other.name;
        transform = other.transform;
        sprite = other.sprite;
        type = other.type;

        other.transform = nullptr;
        other.sprite = nullptr;
    }

    return *this;
}

void SpriteComponent::Update() {
    if (sprite == nullptr) return;

    sprite->Draw();
}

void SpriteComponent::SetTransform(Transform *transform) {
    Component::SetTransform(transform);
    if (sprite != nullptr) {
        sprite->SetCanvas(this->transform->GetRect());
    }
    std::cout << "[" << name << "] Size: X=" << transform->size.x << " Y=" << transform->size.y << "\n";
    std::cout << "[" << name << "] Pos: X=" << transform->position.x << " Y=" << transform->position.y << "\n";
}