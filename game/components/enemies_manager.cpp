#include "enemies_manager.h"
#include "enemy_bullet_controller.h"
#include "galaga.h"
#include "game_object.h"
#include "sound_component.h"
#include <random>

using namespace galaga;
using namespace nim;

uint EnemiesManager::enemiesLeft = 0;

EnemiesManager::EnemiesManager() : columns{12}, rows{4} {
    name = "EnemiesManager";
    transform = nullptr;
}
EnemiesManager::EnemiesManager(const EnemiesManager &other) {
    name = other.name;
    transform = other.transform;
    columns = other.columns;
    rows = other.rows;
}
EnemiesManager::EnemiesManager(EnemiesManager &&other) noexcept {
    name = std::move(other.name);
    transform = other.transform;
    columns = other.columns;
    rows = other.rows;

    other.transform = nullptr;
}
EnemiesManager &EnemiesManager::operator=(const EnemiesManager &other) {
    if (&other != this) {
        transform = nullptr;
        name = other.name;
        transform = other.transform;
        columns = other.columns;
        rows = other.rows;
    }
    return *this;
}
EnemiesManager &EnemiesManager::operator=(EnemiesManager &&other) noexcept {
    if (&other != this) {
        transform = nullptr;
        name = std::move(other.name);
        transform = other.transform;
        columns = other.columns;
        rows = other.rows;

        other.transform = nullptr;
    }
    return *this;
}

void EnemiesManager::Init() {
    CreateGrid();
}

void EnemiesManager::Update() {
    if (prepareForTransition) {
        Galaga::Instance().LoadScene(SceneManager::NextScene());
    }
    if (enemiesLeft <= 0 && !prepareForTransition) {
        prepareForTransition = true;
        auto backgroundMs = Game::Find("Background");
        if (backgroundMs != nullptr) {
            auto sc = backgroundMs->GetComponent<nim::SoundComponent<nim::Music>>("SoundComponent");
            sc->sound.Stop();
        }
    }
}

void EnemiesManager::CreateGrid() {
    float x = offsetX;
    float y = offsetY;
    enemiesLeft = rows * columns;
    for (uint row = 0; row < rows; row++) {
        for (uint column = 0; column < columns; column++) {
            std::shared_ptr<AnimationComponent> graphicComponent = std::make_shared<AnimationComponent>(GenerateEnemy());
            std::shared_ptr<EnemyBulletController> weapon = std::make_shared<EnemyBulletController>();

            Transform t;
            t.Position(x, y);
            t.Size(spriteSize, spriteSize);

            auto go = GameObject::Instantiate(GenerateEnemyName(), t, {graphicComponent, weapon});
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