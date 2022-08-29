#include "bullet.h"
#include "game_object.h"
#include <iostream>

using namespace galaga;

Bullet::Bullet() {
    name = "Bullet";
    transform = nullptr;
}

Bullet::Bullet(const Bullet &other) {
    name = other.name;
    transform = other.transform;
}

Bullet::Bullet(Bullet &&other) {
    name = std::move(other.name);
    transform = other.transform;

    other.transform = nullptr;
}

Bullet::~Bullet() {
    transform = nullptr;
}

Bullet &Bullet::operator=(const Bullet &other) {
    if (&other != this) {
        transform = nullptr;
        name = other.name;
        transform = other.transform;
    }
    return *this;
}

Bullet &Bullet::operator=(Bullet &&other) {
    if (&other != this) {
        transform = nullptr;
        name = std::move(other.name);
        transform = other.transform;

        other.transform = nullptr;
    }
    return *this;
}

void Bullet::Update() {
    transform->position.y -= 10;
    transform->Position(&transform->position);
}

void Bullet::OnCollisionEnter(const nim::GameObject &other) {
    nim::GameObject::Destroy(&other, 1);
    nim::GameObject::Destroy(Component::parent, 1);
}