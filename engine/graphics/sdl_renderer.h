#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H

#include <SDL.h>

#include "renderer.h"

class SDLRenderer : public Renderer
{
public:
    void Init() override;
    void CreateWindow(std::string title, int x_position, int y_position, int width, int height, uint flags) override;
    void CreateRenderer(Color color) override;
    void Update() override;
    void Quit() override;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif //SDL_RENDERER_H