#include "sprite.h"
#include "renderer_locator.h"

using namespace nim;

Sprite::Sprite() {
    auto *rend = dynamic_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
    flip = SDL_RendererFlip::SDL_FLIP_NONE;
}

Sprite::Sprite(const char *id, const char *filename) {
    auto *rend = dynamic_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
    this->id = id;
    this->filename = filename;
    SDL_Surface *loadingSurface = IMG_Load(filename);
    auto tex = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    texture.reset(tex, [](SDL_Texture *tex) { SDL_DestroyTexture(tex); });
    SDL_FreeSurface(loadingSurface);
    flip = SDL_RendererFlip::SDL_FLIP_NONE;
}

Sprite::~Sprite() = default;

Sprite::Sprite(const Sprite &other) {
    id = other.id;
    filename = other.filename;
    texture = other.texture;
    srcCanvas = other.srcCanvas;
    flip = other.flip;
    renderer = other.renderer;
}

Sprite::Sprite(Sprite &&other) noexcept {
    filename = other.filename;
    texture = std::move(other.texture);

    srcCanvas = other.srcCanvas;
    flip = other.flip;

    renderer = other.renderer;

    other.filename = nullptr;
    other.renderer = nullptr;
    other.texture = NULL;
}

Sprite &Sprite::operator=(const Sprite &other) {
    if (&other == this) return *this;
    filename = other.filename;
    texture = other.texture;
    srcCanvas = other.srcCanvas;
    flip = other.flip;

    return *this;
}

Sprite &Sprite::operator=(Sprite &&other) noexcept {
    if (&other == this) return *this;
    filename = other.filename;
    texture = std::move(other.texture);
    srcCanvas = other.srcCanvas;
    flip = other.flip;
    renderer = other.renderer;

    other.filename = nullptr;
    other.renderer = nullptr;
    other.texture = NULL;
    return *this;
}

void Sprite::Draw() {
    SDL_RenderCopyExF(renderer, texture.get(), &srcCanvas, canvas, 0, 0, flip);
}

void Sprite::SetCanvas(SDL_FRect *rect) {
    srcCanvas.x = 0;
    srcCanvas.y = 0;
    srcCanvas.w = static_cast<int>(rect->w);
    srcCanvas.h = static_cast<int>(rect->h);
    canvas = rect;
}

Vector2int Sprite::GetSpriteSize() {
    Vector2int spriteSize;

    if (texture == nullptr) return spriteSize;
    SDL_QueryTexture(texture.get(), NULL, NULL, &spriteSize.x, &spriteSize.y);
    return spriteSize;
}
void Sprite::SetFlip(SpriteFlip newFlip) {
    flip = static_cast<SDL_RendererFlip>(newFlip);
}
