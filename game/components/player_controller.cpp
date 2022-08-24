#include "player_controller.h"
#include "renderer_locator.h"
#include <iostream>

using namespace nim;
using namespace galaga;

PlayerController::PlayerController() {
    name = "PlayerController";
    transform = nullptr;
    input = InputLocator::GetInput();
}

PlayerController::PlayerController(const PlayerController &controller) {
    name = controller.name;
    transform = controller.transform;
    input = controller.input;
}
PlayerController::PlayerController(PlayerController &&controller) {
    name = std::move(controller.name);
    transform = controller.transform;
    input = controller.input;

    controller.transform = nullptr;
    controller.input = nullptr;
}

PlayerController::~PlayerController() {
    transform = nullptr;
    input = nullptr;
}

PlayerController &PlayerController::operator=(const PlayerController &controller) {
    if (&controller != this) {
        transform = nullptr;
        input = nullptr;

        name = controller.name;
        transform = controller.transform;
        input = controller.input;
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

        controller.transform = nullptr;
        controller.input = nullptr;
    }

    return *this;
}

void PlayerController::Update() {
    if (input->GetKeyDown(Key::LEFT) && !(transform->position.x < 0)) {
        transform->position.x -= 1.0f;
        transform->Position(&transform->position);
    }
    auto checkLeftLimit = !(transform->position.x > RendererLocator::GetRenderer()->Width() - transform->size.x);
    if (input->GetKeyDown(Key::RIGHT) && checkLeftLimit) {
        transform->position.x += 1.0f;
        transform->Position(&transform->position);
    }
}