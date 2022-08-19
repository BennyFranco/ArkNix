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
SpriteComponent::SpriteComponent(const char *name, const char *assetName) {
    sprite = nim::AssetManager::Instance().Get<nim::Sprite>(assetName);
    this->name = name;
    transform = nullptr;
    type = ComponentType::Sprite;
}
SpriteComponent::SpriteComponent(Sprite *sprite) : sprite(sprite) {
    name = "SpriteComponent";
    transform = nullptr;
    type = ComponentType::Sprite;
}
SpriteComponent::SpriteComponent(const char *name, Sprite *sprite) : sprite(sprite) {
    this->name = name;
    transform = nullptr;
    type = ComponentType::Sprite;
}
SpriteComponent::SpriteComponent(const SpriteComponent &other) {
    name = other.name;
    transform = other.transform;
    sprite = other.sprite;
    type = other.type;
}
SpriteComponent::SpriteComponent(SpriteComponent &&other) {
    name = other.name;
    transform = other.transform;
    sprite = other.sprite;
    type = other.type;

    other.transform = nullptr;
    other.sprite = nullptr;
}

SpriteComponent::~SpriteComponent() {
    // delete transform;
    // delete sprite;
}

SpriteComponent &SpriteComponent::operator=(const SpriteComponent &other) {
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

void SpriteComponent::Draw() {
    if (sprite == nullptr) return;

    sprite->Draw();
}

void SpriteComponent::SetTransform(Transform *transform) {
    this->transform = transform;
    if (sprite != nullptr) {
        sprite->SetCanvas(this->transform->GetRect());
    }
}