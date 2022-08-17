#include <SDL.h>
#include <iostream>

#include "events/action.h"
#include "input_locator.h"
#include "renderer.h"
#include "renderer_locator.h"

#include "asset_manager/asset_manager.h"
#include "game_object.h"
#include "sprites/sprite.h"

using namespace nim;

int main(int argc, char **args) {
    RendererLocator::Initialize();
    RendererLocator::GetRenderer()->CreateWindow("Nim Engine", SDL_WINDOWPOS_CENTERED,
                                                 SDL_WINDOWPOS_CENTERED,
                                                 800,
                                                 600,
                                                 SDL_WINDOW_SHOWN);
    RendererLocator::GetRenderer()->CreateRenderer(Color(0, 0, 255));

    InputLocator::Initialize();
    AssetManager::Instance().LoadAssets();
    nim::Sprite *s = AssetManager::Instance().Get<nim::Sprite>("ship_6");
    nim::GameObject player("Player", {s});
    Vector2 position = RendererLocator::GetRenderer()->WindowSize();
    position.x = (position.x / 2.f) - 64.f;
    position.y = (position.y / 2.f) - 64.f;
    player.Position(std::move(position));
    player.Size(128, 128);

    while (true) {

        RendererLocator::GetRenderer()->Clear();

        if (InputLocator::GetInput()->GetKeyDown(Key::LEFT)) {
            player.X(player.X() - 1);
        }

        if (InputLocator::GetInput()->GetKeyDown(Key::RIGHT)) {
            player.X(player.X() + 1);
        }

        InputLocator::GetInput()->Update();

        player.Update();
        RendererLocator::GetRenderer()->Update();

        // TODO: Check loop pattern and update this.
        SDL_Delay(16);
    }

    RendererLocator::GetRenderer()->Quit();
    SDL_Quit();
    return 0;
}