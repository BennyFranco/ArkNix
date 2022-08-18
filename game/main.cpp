#include "galaga.h"
#include "scene.h"
#include "sprite_component.h"

int main(int argc, char **args) {
    Galaga newGame;
    newGame.Awake();

    // TEST CODE
    nim::GameObject player("Player");
    player.AddComponent(std::make_shared<nim::SpriteComponent>("ship_6"));
    player.transform->Size(128, 128);
    player.transform->Position(0, 0);

    auto currentScene = std::make_unique<nim::Scene>();
    currentScene->Init();
    currentScene->sceneData->gameObjects.emplace_back(std::move(player));

    newGame.currentScene = std::move(currentScene);
    newGame.Run();
    return 0;
}