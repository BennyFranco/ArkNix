#include <SDL.h>
#include <iostream>

#include "renderer.h"
#include "renderer_locator.h"

int main(int argc, char **args) {
    RendererLocator::Provide();
    RendererLocator::GetRenderer()->CreateWindow("Galaga", SDL_WINDOWPOS_CENTERED,
                                                 SDL_WINDOWPOS_CENTERED,
                                                 800,
                                                 600,
                                                 SDL_WINDOW_SHOWN);
    RendererLocator::GetRenderer()->CreateRenderer(Color(0, 0, 255));

    SDL_Event event;

    while (true) {
        RendererLocator::GetRenderer()->Update();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                        exit(0);
                    break;
                case SDL_QUIT:
                    exit(0);
                    break;

                default:
                    break;
            }
        }
        SDL_Delay(3000);
    }

    RendererLocator::GetRenderer()->Quit();
    SDL_Quit();
    return 0;
}