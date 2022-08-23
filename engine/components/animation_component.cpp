#include "animation_component.h"

using namespace nim;

AnimationComponent::AnimationComponent() : animateOnInit(false), animate(false) {
    transform = nullptr;
    name = "AnimationComponent";
    type = ComponentType::Animation;
    xOffset = 0;
    yOffset = 0;
    frames = 0;
}

AnimationComponent::AnimationComponent(std::string atlasName, bool animateOnInit) : animateOnInit(animateOnInit), animate(false) {
    transform = nullptr;
    name = "AnimationComponent";
    sprite = nim::AssetManager::Instance().Get<Sprite>(atlasName);
    type = ComponentType::Animation;
    xOffset = 0;
    yOffset = 0;
    frames = 0;
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
    frames = other.frames;
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
    frames = other.frames;

    transform = other.transform;
    sprite = std::move(other.sprite);

    other.transform = nullptr;
    other.animate = false;
    other.animateOnInit = false;
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
        sprite = std::move(other.sprite);
        type = other.type;
        animate = other.animate;
        animateOnInit = other.animateOnInit;
        xOffset = other.xOffset;
        yOffset = other.yOffset;
        frames = other.frames;
    }

    return *this;
}

AnimationComponent &AnimationComponent::operator=(AnimationComponent &&other) {
    if (&other != this) {
        transform = nullptr;

        name = other.name;
        transform = other.transform;
        sprite = std::move(other.sprite);
        type = other.type;
        animate = other.animate;
        animateOnInit = other.animateOnInit;
        xOffset = other.xOffset;
        yOffset = other.yOffset;
        frames = other.frames;

        other.transform = nullptr;
        other.animate = false;
        other.animateOnInit = false;
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
    // TODO: Encapsulate SDL_GetTicks() in a time variable.
    // TODO: Expose tick time.
    if (!animate) return;
    if (xOffset != 0 && frames > 0)
        sprite.srcCanvas->x = xOffset * (int) ((SDL_GetTicks() / 100) % frames);
    if (yOffset != 0 && frames > 0)
        sprite.srcCanvas->y = yOffset * (int) ((SDL_GetTicks() / 100) % frames);
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
        sprite.srcCanvas->w = xOffset != 0 ? xOffset : spriteSize.x;
        sprite.srcCanvas->h = yOffset != 0 ? yOffset : spriteSize.y;
    }
}