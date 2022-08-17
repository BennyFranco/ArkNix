#include "renderer_locator.h"

using namespace nim;

std::unique_ptr<Renderer> RendererLocator::renderer;

void RendererLocator::Initialize() {
    renderer = std::make_unique<SDLRenderer>();
    renderer->Init();
}