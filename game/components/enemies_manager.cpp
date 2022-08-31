#include "enemies_manager.h"
#include "game_object.h"
#include <random>

using namespace galaga;
using namespace nim;

EnemiesManager::EnemiesManager() {
    name = "EnemiesManager";
    transform = nullptr;
}
EnemiesManager::EnemiesManager(const EnemiesManager &other) {
    name = other.name;
    transform = other.transform;
}
EnemiesManager::EnemiesManager(EnemiesManager &&other) {
    name = std::move(other.name);
    transform = other.transform;

    other.transform = nullptr;
}
EnemiesManager &EnemiesManager::operator=(const EnemiesManager &other) {
    if (&other != this) {
        transform = nullptr;
        name = other.name;
        transform = other.transform;
    }
    return *this;
}
EnemiesManager &EnemiesManager::operator=(EnemiesManager &&other) {
    if (&other != this) {
        transform = nullptr;
        name = std::move(other.name);
        transform = other.transform;

        other.transform = nullptr;
    }
    return *this;
}

void EnemiesManager::Init() {
    CreateGrid();
}

void EnemiesManager::Update() {}

void EnemiesManager::CreateGrid() {
    float x = offsetX;
    float y = offsetY;
    for (uint row = 0; row < rows; row++) {
        for (uint column = 0; column < columns; column++) {
            std::shared_ptr<AnimationComponent> graphicComponent = std::make_shared<AnimationComponent>(GenerateEnemy());

            Transform t;
            t.Position(x, y);
            t.Size(spriteSize, spriteSize);

            auto go = GameObject::Instantiate(GenerateEnemyName(), t, graphicComponent);
            go->collisionLayer = Layer::Enemy;

            x += offsetX;
        }
        y += offsetY;
        x = offsetX;
    }
}

nim::AnimationComponent EnemiesManager::GenerateEnemy() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, 2);

    switch (distribution(gen)) {
        case 0:
            return GenerateAlan();
        case 1:
            return GenerateBonBon();
        case 2:
            return GenerateLips();
    }
    return GenerateAlan();
}

std::string EnemiesManager::GenerateEnemyName() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, 1000000);

    return std::string("Enemy_") + std::to_string(distribution(gen));
}

nim::AnimationComponent EnemiesManager::GenerateAlan() {
    AnimationComponent graphicComponent{"alan", true};
    graphicComponent.xOffset = 16;
    graphicComponent.yOffset = 0;
    graphicComponent.frames = 6;

    return graphicComponent;
}

nim::AnimationComponent EnemiesManager::GenerateBonBon() {
    AnimationComponent graphicComponent{"bon_bon", true};
    graphicComponent.xOffset = 16;
    graphicComponent.yOffset = 0;
    graphicComponent.frames = 4;

    return graphicComponent;
}
nim::AnimationComponent EnemiesManager::GenerateLips() {
    AnimationComponent graphicComponent{"lips", true};
    graphicComponent.xOffset = 16;
    graphicComponent.yOffset = 0;
    graphicComponent.frames = 5;

    return graphicComponent;
}