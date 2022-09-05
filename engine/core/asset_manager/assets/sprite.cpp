#include "sprite.h"
#include "renderer_locator.h"

using namespace nim;

Sprite::Sprite() {
    SDLRenderer *rend = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
    // srcCanvas = std::make_shared<SDL_Rect>();
}

Sprite::Sprite(const char *id, const char *filename) {
    SDLRenderer *rend = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
    this->id = id;
    SDL_Surface *loadingSurface = IMG_Load(filename);
    auto tex = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    texture.reset(tex, [](SDL_Texture *tex) { SDL_DestroyTexture(tex); });
    SDL_FreeSurface(loadingSurface);
    this->filename = filename;
}

Sprite::~Sprite() = default;

Sprite::Sprite(const Sprite &other) {
    id = other.id;
    filename = other.filename;
    texture = other.texture;
    srcCanvas = other.srcCanvas;
}

Sprite::Sprite(Sprite &&other) {
    filename = other.filename;
    texture = std::move(other.texture);

    srcCanvas = std::move(other.srcCanvas);

    other.filename = nullptr;
    other.texture = NULL;
}

Sprite &Sprite::operator=(const Sprite &other) {
    if (&other == this) return *this;
    filename = other.filename;
    texture = other.texture;
    // srcCanvas.reset();
    srcCanvas = other.srcCanvas;

    return *this;
}

Sprite &Sprite::operator=(Sprite &&other) {
    if (&other == this) return *this;
    filename = other.filename;
    texture = std::move(other.texture);
    // srcCanvas = std::move(other.srcCanvas);
    srcCanvas = other.srcCanvas;
    other.texture = NULL;
    return *this;
}

void Sprite::Draw() {
    // SDL_RenderCopyF(renderer, texture, srcCanvas.get(), canvas);
    // SDL_RenderCopyF(renderer, texture, NULL, NULL);
    SDL_RenderCopyExF(renderer, texture.get(), &srcCanvas, canvas, 0, 0, SDL_FLIP_NONE);
}

void Sprite::SetCanvas(SDL_FRect *rect) {
    srcCanvas.x = 0;
    srcCanvas.y = 0;
    srcCanvas.w = rect->w;
    srcCanvas.h = rect->h;
    canvas = rect;
}

Vector2int Sprite::GetSpriteSize() {
    Vector2int spriteSize;

    if (texture == nullptr) return spriteSize;
    SDL_QueryTexture(texture.get(), NULL, NULL, &spriteSize.x, &spriteSize.y);
    return spriteSize;
}