#include "sprite.h"
#include "renderer_locator.h"

using namespace nim;

Sprite::Sprite() {
    SDLRenderer *rend = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
    texture = NULL;
    srcCanvas = std::make_unique<SDL_Rect>();
}

Sprite::Sprite(const char *id, const char *filename) {
    SDLRenderer *rend = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
    this->id = id;
    Load(filename);
    srcCanvas = std::make_unique<SDL_Rect>();
}

Sprite::~Sprite() {
    if (texture != NULL)
        SDL_DestroyTexture(texture);
}

Sprite::Sprite(const Sprite &other) {
    filename = other.filename;
    texture = other.texture;
    srcCanvas = std::make_unique<SDL_Rect>();
    srcCanvas->x = other.srcCanvas->x;
    srcCanvas->y = other.srcCanvas->y;
    srcCanvas->w = other.srcCanvas->x;
    srcCanvas->h = other.srcCanvas->h;
}

Sprite::Sprite(Sprite &&other) {
    filename = other.filename;
    texture = other.texture;

    srcCanvas = std::move(other.srcCanvas);

    other.filename = nullptr;
    other.texture = NULL;
}

Sprite &Sprite::operator=(const Sprite &other) {
    if (&other == this) return *this;
    SDL_DestroyTexture(texture);
    filename = other.filename;
    texture = other.texture;

    srcCanvas.reset(new SDL_Rect());
    srcCanvas->x = other.srcCanvas->x;
    srcCanvas->y = other.srcCanvas->y;
    srcCanvas->w = other.srcCanvas->x;
    srcCanvas->h = other.srcCanvas->h;

    return *this;
}

Sprite &Sprite::operator=(Sprite &&other) {
    if (&other == this) return *this;

    SDL_DestroyTexture(texture);

    filename = other.filename;
    texture = other.texture;

    srcCanvas = std::move(other.srcCanvas);

    other.filename = nullptr;
    other.texture = NULL;
    return *this;
}

bool Sprite::Load(const char *filename) {
    SDL_Surface *loadingSurface = IMG_Load(filename);
    texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
    this->filename = filename;

    // int w, h;
    // SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    return true;
}

void Sprite::Draw() {
    // SDL_RenderCopyF(renderer, texture, srcCanvas.get(), canvas);
    // SDL_RenderCopyF(renderer, texture, NULL, NULL);
    SDL_RenderCopyExF(renderer, texture, srcCanvas.get(), canvas, 0, 0, SDL_FLIP_NONE);
}

void Sprite::SetCanvas(SDL_FRect *rect) {
    srcCanvas->x = 0;
    srcCanvas->y = 0;
    srcCanvas->w = rect->w;
    srcCanvas->h = rect->h;
    canvas = rect;
}

Vector2int Sprite::GetSpriteSize() {
    Vector2int spriteSize;

    if (texture == nullptr) return spriteSize;
    SDL_QueryTexture(texture, NULL, NULL, &spriteSize.x, &spriteSize.y);
    return spriteSize;
}