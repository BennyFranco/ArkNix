#include "animation_component.h"

using namespace nim;

AnimationComponent::AnimationComponent() : sprite(nullptr), animateOnInit(false), animate(false) {
    transform = nullptr;
    name = "AnimationComponent";
    type = ComponentType::Animation;
    xOffset = 0;
    yOffset = 0;
}

AnimationComponent::AnimationComponent(std::string atlasName, bool animateOnInit) : animateOnInit(animateOnInit), animate(false) {
    transform = nullptr;
    name = "AnimationComponent";
    sprite = nim::AssetManager::Instance().Get<nim::Sprite>(atlasName);
    type = ComponentType::Animation;
    xOffset = 0;
    yOffset = 0;
}

AnimationComponent::AnimationComponent(const AnimationComponent &other) {
    std::cout << "[AnimationComponent] Copy Constructor"
              << "\n";
    name = other.name;
    transform = other.transform;
    sprite = other.sprite;
    type = other.type;
    animate = other.animate;
    animateOnInit = other.animateOnInit;
    xOffset = other.xOffset;
    yOffset = other.yOffset;
}

AnimationComponent::AnimationComponent(AnimationComponent &&other) {
    std::cout << "[AnimationComponent] Move Constructor"
              << "\n";
    name = other.name;
    type = other.type;
    animate = other.animate;
    animateOnInit = other.animateOnInit;
    xOffset = other.xOffset;
    yOffset = other.yOffset;

    transform = other.transform;
    sprite = other.sprite;

    other.transform = nullptr;
    other.sprite = nullptr;
    other.animate = false;
    other.animateOnInit = false;
    xOffset = 0;
    yOffset = 0;
}

AnimationComponent::~AnimationComponent() {
    transform = nullptr;
    sprite = nullptr;
}

AnimationComponent &AnimationComponent::operator=(const AnimationComponent &other) {
    if (&other != this) {
        transform = nullptr;
        sprite = nullptr;

        name = other.name;
        transform = other.transform;
        sprite = other.sprite;
        type = other.type;
        animate = other.animate;
        animateOnInit = other.animateOnInit;
        xOffset = other.xOffset;
        yOffset = other.yOffset;
    }

    return *this;
}

AnimationComponent &AnimationComponent::operator=(AnimationComponent &&other) {
    if (&other != this) {
        transform = nullptr;
        sprite = nullptr;

        name = other.name;
        transform = other.transform;
        sprite = other.sprite;
        type = other.type;
        animate = other.animate;
        animateOnInit = other.animateOnInit;
        xOffset = other.xOffset;
        yOffset = other.yOffset;

        other.transform = nullptr;
        other.sprite = nullptr;
        other.animate = false;
        other.animateOnInit = false;
        xOffset = 0;
        yOffset = 0;
    }

    return *this;
}

void AnimationComponent::Init() {
    if (animateOnInit) Play();
}

void AnimationComponent::Update() {
    if (sprite == nullptr) return;
    Animate();
    sprite->Draw();
}

void AnimationComponent::Quit() {
    Stop();
}

void AnimationComponent::Animate() {
    // TODO: Add logic here for animation
}

void AnimationComponent::Play() {
    animate = true;
}

void AnimationComponent::Stop() {
    animate = false;
}