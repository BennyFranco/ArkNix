#include "animation_component.h"
#include "ntime.h"

using namespace nim;

AnimationComponent::AnimationComponent() : animateOnInit(false), animate(false),
                                           xOffset(0), yOffset(0), frames(0) {
    transform = nullptr;
    name = "AnimationComponent";
}

AnimationComponent::AnimationComponent(const std::string &atlasName, bool animateOnInit) : animate(false) {
    transform = nullptr;
    name = "AnimationComponent";
    sprite = nim::AssetManager::Instance().Get<Sprite>(atlasName);
    xOffset = 0;
    yOffset = 0;
    frames = 0;
    this->animateOnInit = animateOnInit;
}

AnimationComponent::AnimationComponent(const AnimationComponent &other) {
    std::cout << "[AnimationComponent] Copy Constructor"
              << "\n";
    name = other.name;
    transform = other.transform;
    sprite = other.sprite;
    animateOnInit = other.animateOnInit;
    animate = other.animate;
    xOffset = other.xOffset;
    yOffset = other.yOffset;
    frames = other.frames;
}

AnimationComponent::AnimationComponent(AnimationComponent &&other) noexcept {
    std::cout << "[AnimationComponent] Move Constructor"
              << "\n";
    name = other.name;
    animateOnInit = other.animateOnInit;
    animate = other.animate;
    xOffset = other.xOffset;
    yOffset = other.yOffset;
    frames = other.frames;

    transform = other.transform;
    sprite = std::move(other.sprite);

    other.transform = nullptr;
    other.animateOnInit = false;
    other.animate = false;
    other.xOffset = 0;
    other.yOffset = 0;
    other.frames = 0;
}

AnimationComponent::~AnimationComponent() {
    transform = nullptr;
}

AnimationComponent &AnimationComponent::operator=(const AnimationComponent &other) {
    if (&other != this) {
        transform = nullptr;

        name = other.name;
        transform = other.transform;
        sprite = other.sprite;
        animateOnInit = other.animateOnInit;
        xOffset = other.xOffset;
        yOffset = other.yOffset;
        frames = other.frames;
    }

    return *this;
}

AnimationComponent &AnimationComponent::operator=(AnimationComponent &&other) noexcept {
    if (&other != this) {
        transform = nullptr;

        name = other.name;
        transform = other.transform;
        sprite = std::move(other.sprite);
        animateOnInit = other.animateOnInit;
        animate = other.animate;
        xOffset = other.xOffset;
        yOffset = other.yOffset;
        frames = other.frames;

        other.transform = nullptr;
        other.animateOnInit = false;
        other.animate = false;
        other.xOffset = 0;
        other.yOffset = 0;
        other.frames = 0;
    }

    return *this;
}

void AnimationComponent::Init() {
    if (animateOnInit) Play();
}

void AnimationComponent::Update() {
    if (sprite.filename.empty()) return;
    Animate();
    sprite.Draw();
}

void AnimationComponent::Quit() {
    Stop();
}

void AnimationComponent::Animate() {
    if (!animate) return;

    auto spriteNum = (uint) ((NimTime::Instance().GetTicks() / 100) % frames);
    if (xOffset != 0 && frames > 0)
        sprite.srcCanvas.x = xOffset * static_cast<int>(spriteNum);
    if (yOffset != 0 && frames > 0)
        sprite.srcCanvas.y = yOffset * static_cast<int>(spriteNum);
}

void AnimationComponent::Play() {
    animate = true;
}

void AnimationComponent::Stop() {
    animate = false;
}

void AnimationComponent::SetTransform(Transform *transform) {
    Component::SetTransform(transform);
    if (!sprite.filename.empty()) {
        sprite.SetCanvas(this->transform->GetRect());
        auto spriteSize = sprite.GetSpriteSize();
        sprite.srcCanvas.w = xOffset != 0 ? xOffset : spriteSize.x;
        sprite.srcCanvas.h = yOffset != 0 ? yOffset : spriteSize.y;
    }
}