#include "sprite_component.h"
#include "asset_manager.h"

using namespace nim;

SpriteComponent::SpriteComponent() {
    name = "SpriteComponent";
    transform = nullptr;
}

SpriteComponent::SpriteComponent(const char *assetName) {
    name = "SpriteComponent";
    transform = nullptr;
    sprite = nim::AssetManager::Instance().Get<Sprite>(assetName);
}
SpriteComponent::SpriteComponent(const SpriteComponent &other) {
    std::cout << "[SpriteComponent] Copy Constructor"
              << "\n";
    name = other.name;
    transform = other.transform;
    sprite = other.sprite;
}
SpriteComponent::SpriteComponent(SpriteComponent &&other) noexcept {
    std::cout << "[SpriteComponent] Move Constructor"
              << "\n";
    name = other.name;

    transform = other.transform;
    sprite = std::move(other.sprite);

    other.transform = nullptr;
}

SpriteComponent::~SpriteComponent() {
    transform = nullptr;
}

SpriteComponent &SpriteComponent::operator=(const SpriteComponent &other) {
    std::cout << "[SpriteComponent] Copy operator"
              << "\n";
    if (&other != this) {
        transform = nullptr;

        name = other.name;
        transform = other.transform;
        sprite = other.sprite;
    }

    return *this;
}
SpriteComponent &SpriteComponent::operator=(SpriteComponent &&other) noexcept {
    std::cout << "[SpriteComponent] Move operator"
              << "\n";
    if (&other != this) {
        transform = nullptr;

        name = other.name;
        transform = other.transform;
        sprite = std::move(other.sprite);

        other.transform = nullptr;
    }

    return *this;
}

void SpriteComponent::Update() {
    if (sprite.filename.empty()) return;

    sprite.Draw();
}

void SpriteComponent::SetTransform(Transform *transform) {
    Component::SetTransform(transform);
    if (!sprite.filename.empty()) {
        sprite.SetCanvas(this->transform->GetRect());
    }
}