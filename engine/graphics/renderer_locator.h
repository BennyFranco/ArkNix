#ifndef RENDERER_SERVICE_LOCATOR_H
#define RENDERER_SERVICE_LOCATOR_H

#include <memory>
#include "renderer.h"
#include "sdl_renderer.h"

class RendererLocator {
public:
    static Renderer *GetRenderer() { return renderer.get(); }
    static void Provide() {
        renderer = std::make_unique<SDLRenderer>();
        renderer->Init();
    }

private:
    static std::unique_ptr<Renderer> renderer;
};

#endif