#include "bullet.h"
#include "enemies_manager.h"
#include "game_object.h"
#include "player_data.h"
#include <iostream>

using namespace galaga;

Bullet::Bullet() {
    name = "Bullet";
    transform = nullptr;
    direction = nim::Direction::Up;
}

Bullet::Bullet(nim::Direction dir) {
    name = "Bullet";
    transform = nullptr;
    direction = dir;
}

Bullet::Bullet(const Bullet &other) {
    name = other.name;
    transform = other.transform;
    direction = other.direction;
}

Bullet::Bullet(Bullet &&other) {
    name = std::move(other.name);
    transform = other.transform;
    direction = other.direction;

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
        direction = other.direction;
    }
    return *this;
}

Bullet &Bullet::operator=(Bullet &&other) {
    if (&other != this) {
        transform = nullptr;
        name = std::move(other.name);
        transform = other.transform;
        direction = other.direction;

        other.transform = nullptr;
    }
    return *this;
}

void Bullet::Update() {
    transform->position.y += 10 * (float) direction;
    transform->Position(&transform->position);
}

void Bullet::OnCollisionEnter(const nim::GameObject &other) {
    if (other.collisionLayer == nim::Layer::Enemy) {
        PlayerData::Instance().score += 100;
        EnemiesManager::enemiesLeft -= 1;
        std::cout << "Enemies Left: " << EnemiesManager::enemiesLeft << "\n";
    }
    nim::GameObject::Destroy(&other, 1);
    nim::GameObject::Destroy(Component::parent, 1);
}