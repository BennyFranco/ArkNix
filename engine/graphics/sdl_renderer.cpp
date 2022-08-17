#include "sdl_renderer.h"

using namespace nim;

void SDLRenderer::Init() {
    SDL_Init(SDL_INIT_VIDEO);
}

void SDLRenderer::CreateWindow(std::string title, int x_position, int y_position, int width, int height, uint flags) {
    window = SDL_CreateWindow(
            title.c_str(),
            x_position,
            y_position,
            width,
            height,
            flags);
}

void SDLRenderer::SetWindowTitle(std::string title) {
    SDL_SetWindowTitle(window, title.c_str());
}

void SDLRenderer::CreateRenderer(Color color) {
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
}

void SDLRenderer::Clear() {
    SDL_RenderClear(renderer);
}

void SDLRenderer::Update() {
    SDL_RenderPresent(renderer);
}

void SDLRenderer::Quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

int SDLRenderer::Width() {
    int w;
    SDL_GetWindowSize(window, &w, NULL);
    return w;
}
int SDLRenderer::Height() {
    int h;
    SDL_GetWindowSize(window, NULL, &h);
    return h;
}
Vector2 SDLRenderer::WindowSize() {
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    return Vector2(w, h);
}