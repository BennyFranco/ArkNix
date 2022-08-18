#include "galaga.h"
#include "scene.h"
#include "sprite.h"

int main(int argc, char **args) {
    Galaga newGame;
    newGame.Awake();

    // TEST CODE
    nim::GameObject player("Player");
    nim::Sprite *sprite = nim::AssetManager::Instance().Get<nim::Sprite>("ship_6");
    player.AddComponent("texture", sprite);
    player.transform->Size(128, 128);
    player.transform->Position(sprite->Centered());

    auto currentScene = std::make_unique<nim::Scene>();
    currentScene->Init();
    currentScene->sceneData->gameObjects.emplace_back(std::move(player));

    newGame.currentScene = std::move(currentScene);
    newGame.Run();
    return 0;
}