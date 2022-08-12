#include <iostream>
#include <SDL.h>

void Update(SDL_Renderer *renderer)
{
    SDL_Event event;

    while (true)
    {
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
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
}

int main(int argc, char **args)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Galaga", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          808,
                                          600,
                                          SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    Update(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
