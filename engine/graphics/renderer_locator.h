#ifndef RENDERER_SERVICE_LOCATOR_H
#define RENDERER_SERVICE_LOCATOR_H

#include "renderer.h"
#include "sdl_renderer.h"
#include <memory>

namespace nim {
    class RendererLocator {
    public:
        static Renderer *GetRenderer() { return renderer.get(); }
        static void Initialize();

    private:
        static std::unique_ptr<Renderer> renderer;
    };
}// namespace nim
#endif