#include <SDL.h>
#include <iostream>

#include "events/action.h"
#include "input_locator.h"
#include "keyboard.h"
#include "renderer.h"
#include "renderer_locator.h"

#include "asset_manager/asset_manager.h"
#include "sprites/sprite.h"

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

    while (true) {

        InputLocator::GetInput()->Update();
        RendererLocator::GetRenderer()->Clear();
        s->Draw();
        RendererLocator::GetRenderer()->Update();

        // TODO: Check loop pattern and update this.
        SDL_Delay(16);
    }

    RendererLocator::GetRenderer()->Quit();
    SDL_Quit();
    return 0;
}