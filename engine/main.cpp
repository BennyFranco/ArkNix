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

const uint kTargetFps = 60;
const uint kDelayTime = 1000.f / kTargetFps;

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
    int fps = 0;

    uint timestamp = SDL_GetTicks();
    while (true) {
        uint frameStart = SDL_GetTicks();

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

        uint frameEnd = SDL_GetTicks();
        uint frameDuration = frameEnd - frameStart;

        if ((frameEnd - timestamp) >= 1000) {
            RendererLocator::GetRenderer()->SetWindowTitle(std::string("Nim Engine - FPS: " + std::to_string(fps)));
            fps = 0;
            timestamp = frameEnd;
        }

        if (frameDuration < kDelayTime) {
            SDL_Delay(kDelayTime - frameDuration);
        }
        fps++;
    }

    RendererLocator::GetRenderer()->Quit();
    SDL_Quit();
    return 0;
}