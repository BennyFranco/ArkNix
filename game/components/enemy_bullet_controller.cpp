#include "enemy_bullet_controller.h"
#include "animation_component.h"
#include "bullet.h"
#include "game_object.h"
#include "scene_manager.h"
#include <memory>
#include <random>

using namespace galaga;
using namespace nim;

EnemyBulletController::EnemyBulletController() {
    name = "EnemyBulletController";
    transform = nullptr;
}

EnemyBulletController::EnemyBulletController(const EnemyBulletController &other) {
    name = other.name;
    transform = other.transform;
}

EnemyBulletController::EnemyBulletController(EnemyBulletController &&other) noexcept {
    name = std::move(other.name);
    transform = other.transform;
    other.transform = nullptr;
}

EnemyBulletController::~EnemyBulletController() {
    transform = nullptr;
}

EnemyBulletController &EnemyBulletController::operator=(const EnemyBulletController &other) {
    if (&other != this) {
        transform = nullptr;

        name = other.name;
        transform = other.transform;
    }

    return *this;
}

EnemyBulletController &EnemyBulletController::operator=(EnemyBulletController &&other) noexcept {
    if (&other != this) {
        transform = nullptr;

        name = std::move(other.name);
        transform = other.transform;

        other.transform = nullptr;
    }

    return *this;
}

void EnemyBulletController::Update() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 10000);
    std::uniform_int_distribution<> conditionDist(9990, 9999);
    int condition = 9999;
    if (SceneManager::currentIndex > 3) {
        condition = conditionDist(gen);
    }

    if (distr(gen) >= condition) {
        Fire();
    }
}

void EnemyBulletController::Fire() {
    std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(nim::Direction::Down);
    std::shared_ptr<AnimationComponent> graphicComponent = std::make_shared<AnimationComponent>("shot", true);
    graphicComponent->xOffset = 12;
    graphicComponent->yOffset = 0;
    graphicComponent->frames = 2;
    graphicComponent->sprite.SetFlip(SpriteFlip::Vertical);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 1000000);

    Transform t(*transform);
    t.position.y -= (t.size.y / 2.f) - 24;
    t.size.x = 12;
    t.size.y = 24;

    auto go = GameObject::Instantiate("bullet_" + std::to_string(distr(gen)), std::move(t), {graphicComponent, bullet});
    go->collisionLayer = Layer::EnemyBullet;
}
