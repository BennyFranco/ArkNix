#include <SDL.h>
#include <iostream>

#include "events/action.h"
#include "input_locator.h"
#include "keyboard.h"
#include "renderer.h"
#include "renderer_locator.h"

void print(int i) {
    std::cout << "YES! num=" << i << std::endl;
}

void printKey(SDL_KeyboardEvent *event) {
    std::cout << "KEY=" << event->keysym.sym << std::endl;
}

int main(int argc, char **args) {
    RendererLocator::Initialize();
    RendererLocator::GetRenderer()->CreateWindow("Galaga", SDL_WINDOWPOS_CENTERED,
                                                 SDL_WINDOWPOS_CENTERED,
                                                 800,
                                                 600,
                                                 SDL_WINDOW_SHOWN);
    RendererLocator::GetRenderer()->CreateRenderer(Color(0, 0, 255));

    InputLocator::Initialize();

    while (true) {
        RendererLocator::GetRenderer()->Update();
        InputLocator::GetInput()->Update();
        std::cout << Keyboard::GetKeyDown(Key::A) << std::endl;
        SDL_Delay(16);
        // testAction.Invoke(1);
    }

    RendererLocator::GetRenderer()->Quit();
    SDL_Quit();
    return 0;
}