#include "bullet_controller.h"
#include "animation_component.h"
#include "game_object.h"
#include <memory>

using namespace nim;
using namespace galaga;

BulletController::BulletController() {
    name = "BulletController";
    transform = nullptr;
    input = InputLocator::GetInput();
    // bullet = nullptr;
}

BulletController::BulletController(const BulletController &other) {
    name = other.name;
    transform = other.transform;
    input = other.input;
    // bullet = other.bullet;
}

BulletController::BulletController(BulletController &&other) {
    name = std::move(other.name);
    // bullet = std::move(other.bullet);
    transform = other.transform;
    input = other.input;

    other.transform = nullptr;
    other.input = nullptr;
}

BulletController::~BulletController() {
    transform = nullptr;
}

BulletController &BulletController::operator=(const BulletController &other) {
    if (&other != this) {
        transform = nullptr;
        input = nullptr;

        name = other.name;
        transform = other.transform;
        input = other.input;
        // bullet = other.bullet;
    }

    return *this;
}

BulletController &BulletController::operator=(BulletController &&other) {
    if (&other != this) {
        transform = nullptr;
        input = nullptr;

        name = std::move(other.name);
        // bullet = std::move(other.bullet);
        transform = other.transform;
        input = other.input;

        other.transform = nullptr;
        other.input = nullptr;
    }

    return *this;
}

void BulletController::Update() {
    if (input->GetKeyUp(Key::LEFT_CTRL) || input->GetKeyUp(Key::RIGHT_CTRL)) {
        Fire();
    }
}


void BulletController::Fire() {
    std::shared_ptr<AnimationComponent> graphicComponent = std::make_shared<AnimationComponent>("shot", true);
    graphicComponent->xOffset = 48;
    graphicComponent->yOffset = 0;
    graphicComponent->frames = 2;

    Transform t(Vector2(48, 48), Vector2(50, 100));
    auto go = GameObject::Instantiate("bullet", t, graphicComponent);
    GameObject::Destroy(go, 2000);
}