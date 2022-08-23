#include "galaga.h"
#include "parse_components.h"

void Galaga::Awake() {
    windowProperties.width = 720;
    windowProperties.height = 960;
    windowProperties.title = "Galaga";
    nim::RegisterCustomComponents();
    nim::Game::Awake();
}