#include "galaga.h"
#include "parse_components.h"

using namespace galaga;

Galaga &Galaga::Instance() {
    static std::unique_ptr<Galaga> instance{new Galaga()};
    return *instance;
}

void Galaga::Awake() {
    windowProperties.width = 1024;
    windowProperties.height = 784;
    windowProperties.title = "Galaga";
    nim::RegisterCustomComponents();
    nim::Game::Awake();
}