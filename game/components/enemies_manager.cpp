#include "enemies_manager.h"
#include "animation_component.h"
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
EnemiesManager::~EnemiesManager() {}

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
    for (uint i = 0; i < rowSize; i++) {
        std::shared_ptr<AnimationComponent> graphicComponent = std::make_shared<AnimationComponent>("alan", true);
        graphicComponent->xOffset = 16;
        graphicComponent->yOffset = 0;
        graphicComponent->frames = 6;

        Transform t;
        t.Position(x, 48);
        t.Size(spriteSize, spriteSize);

        auto go = GameObject::Instantiate(GenerateEnemyName(), t, graphicComponent);
        go->collisionLayer = Layer::Enemy;

        x += offsetX;
    }
}

std::string EnemiesManager::GenerateEnemyName() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 1000000);

    return std::string("Enemy_") + std::to_string(distr(gen));
}