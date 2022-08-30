#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "renderer.h"

namespace nim {
    class SDLRenderer : public Renderer {
    public:
        void Init() override;
        void CreateWindow(std::string title, int x_position,
                          int y_position, int width, int height, uint flags) override;
        void CreateWindow(std::string title, int width, int height) override;
        void SetWindowTitle(std::string title) override;
        void CreateRenderer(Color color) override;
        void Clear() override;
        void Update() override;
        void Quit() override;
        int Width() override;
        int Height() override;
        Vector2int WindowSize() override;

    public:
        SDL_Renderer *Renderer() const { return renderer; }

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
    };
}// namespace nim
#endif//SDL_RENDERER_H