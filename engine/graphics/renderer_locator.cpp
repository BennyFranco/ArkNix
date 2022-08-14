#include "renderer_locator.h"

std::unique_ptr<Renderer> RendererLocator::renderer;

void RendererLocator::Initialize() {
    renderer = std::make_unique<SDLRenderer>();
    renderer->Init();
}