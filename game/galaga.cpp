#include "galaga.h"
#include "parse_components.h"

void Galaga::Awake() {
    windowProperties.width = 1024;
    windowProperties.height = 784;
    windowProperties.title = "Galaga";
    nim::RegisterCustomComponents();
    nim::Game::Awake();
}