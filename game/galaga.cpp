#include "galaga.h"

void Galaga::Awake() {
    windowProperties.width = 720;
    windowProperties.height = 960;
    windowProperties.title = "Galaga";
    nim::Game::Awake();
}