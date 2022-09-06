#include "sound_component.h"

using namespace nim;

SoundComponent::SoundComponent() {
    transform = nullptr;
    name = "SoundComponent";
}

SoundComponent::SoundComponent(std::string soundName) {
    transform = nullptr;
    name = "SoundComponent";
    sound = AssetManager::Instance().Get<Sound>(soundName);
}

SoundComponent::SoundComponent(const SoundComponent &other) {
    name = other.name;
    transform = other.transform;
    sound = other.sound;
}

SoundComponent::SoundComponent(SoundComponent &&other) {
    name = other.name;
    transform = other.transform;
    sound = std::move(other.sound);

    other.transform = nullptr;
}

SoundComponent::~SoundComponent() {
    transform = nullptr;
}

SoundComponent &SoundComponent::operator=(const SoundComponent &other) {
    if (&other != this) {
        transform = nullptr;

        name = other.name;
        transform = other.transform;
        sound = other.sound;
    }

    return *this;
}

SoundComponent &SoundComponent::operator=(SoundComponent &&other) {
    if (&other != this) {
        transform = nullptr;

        name = other.name;
        transform = other.transform;
        sound = std::move(other.sound);

        other.transform = nullptr;
    }

    return *this;
}

void SoundComponent::Play() {
    sound.Play();
}