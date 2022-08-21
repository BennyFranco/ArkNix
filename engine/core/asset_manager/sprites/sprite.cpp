#include "sprite.h"
#include "renderer_locator.h"

using namespace nim;

Sprite::Sprite() {
    SDLRenderer *rend = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
    texture = NULL;
}

Sprite::Sprite(const char *id, const char *filename) {
    SDLRenderer *rend = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
    this->id = id;
    Load(filename);
}

Sprite::~Sprite() {
    if (texture != NULL)
        SDL_DestroyTexture(texture);
}

Sprite::Sprite(const Sprite &other) {
    filename = other.filename;
    texture = other.texture;
}

Sprite::Sprite(Sprite &&other) {
    filename = other.filename;
    texture = other.texture;

    other.filename = nullptr;
    other.texture = NULL;
}

Sprite &Sprite::operator=(const Sprite &other) {
    if (&other == this) return *this;
    SDL_DestroyTexture(texture);
    filename = other.filename;
    texture = other.texture;

    return *this;
}

Sprite &Sprite::operator=(Sprite &&other) {
    if (&other == this) return *this;

    SDL_DestroyTexture(texture);

    filename = other.filename;
    texture = other.texture;

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
    SDL_RenderCopyF(renderer, texture, &srcCanvas, canvas);
    // SDL_RenderCopyF(renderer, texture, NULL, NULL);
}

void Sprite::SetCanvas(SDL_FRect *rect) {
    srcCanvas.x = 0;
    srcCanvas.y = 0;
    srcCanvas.w = rect->w;
    srcCanvas.h = rect->h;
    canvas = rect;
    // canvas.x = rect->x;
    // canvas.y = rect->y;
    // canvas.w = rect->w;
    // canvas.h = rect->h;
}