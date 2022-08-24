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

void SDLRenderer::CreateWindow(std::string title, int width, int height) {
    window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_SHOWN);
}

void SDLRenderer::SetWindowTitle(std::string title) {
    SDL_SetWindowTitle(window, title.c_str());
}

void SDLRenderer::CreateRenderer(Color color) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
    SDL_Quit();
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
Vector2int SDLRenderer::WindowSize() {
    Vector2int size;
    SDL_GetRendererOutputSize(renderer, &size.x, &size.y);
    return size;
}