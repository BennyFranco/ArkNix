#include "player_controller.h"
#include "galaga.h"
#include "game.h"
#include "player_data.h"
#include "renderer_locator.h"
#include <iostream>

using namespace nim;
using namespace galaga;

PlayerController::PlayerController() {
    name = "PlayerController";
    transform = nullptr;
    scoreLabel = nullptr;
    input = InputLocator::GetInput();
    velocity = 1;
}

PlayerController::PlayerController(const PlayerController &controller) {
    name = controller.name;
    transform = controller.transform;
    input = controller.input;
    velocity = controller.velocity;
    scoreLabel = controller.scoreLabel;
}

PlayerController::PlayerController(PlayerController &&controller) {
    name = std::move(controller.name);
    transform = controller.transform;
    input = controller.input;
    velocity = controller.velocity;
    scoreLabel = controller.scoreLabel;

    controller.transform = nullptr;
    controller.input = nullptr;
    controller.velocity = 0;
    controller.scoreLabel = nullptr;
}

PlayerController::~PlayerController() {
    transform = nullptr;
    scoreLabel = nullptr;
    input = nullptr;
}

PlayerController &PlayerController::operator=(const PlayerController &controller) {
    if (&controller != this) {
        transform = nullptr;
        input = nullptr;

        name = controller.name;
        transform = controller.transform;
        input = controller.input;
        velocity = controller.velocity;
    }

    return *this;
}

PlayerController &PlayerController::operator=(PlayerController &&controller) {
    if (&controller != this) {
        transform = nullptr;
        input = nullptr;

        name = std::move(controller.name);
        transform = controller.transform;
        input = controller.input;
        velocity = controller.velocity;

        controller.transform = nullptr;
        controller.input = nullptr;
        controller.velocity = 0;
    }

    return *this;
}

void PlayerController::Init() {
    auto scoreGo = Game::Find("Score");
    if (scoreGo != nullptr)
        scoreLabel = scoreGo->GetComponent<TextComponent>("TextComponent");
}

void PlayerController::Update() {
    if (input->GetKeyDown(Key::LEFT) && !(transform->position.x < 0)) {
        transform->position.x -= velocity;
        transform->Position(&transform->position);
    }
    auto checkRightLimit = !(transform->position.x > 720 - transform->size.x);
    if (input->GetKeyDown(Key::RIGHT) && checkRightLimit) {
        transform->position.x += velocity;
        transform->Position(&transform->position);
    }

    SetScoreLabel(PlayerData::Instance().score);
}

void PlayerController::Quit() {
    Galaga::Instance().Pause();
    PlayerData::Instance().score = 0;
    std::thread reloadScene([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Galaga::Instance().ReloadScene();
    });
    reloadScene.detach();
}
void PlayerController::SetScoreLabel(long score) {
    if (scoreLabel == nullptr) return;
    scoreLabel->Text("Score: " + std::to_string(score));
}
