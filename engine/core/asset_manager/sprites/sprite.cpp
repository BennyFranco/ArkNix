#include "sprite.h"
#include "renderer_locator.h"

using namespace nim;

Sprite::Sprite() {
    SDLRenderer *rend = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
    texture = NULL;
}

Sprite::Sprite(const char *filename) {
    SDLRenderer *rend = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
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

    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    return true;
}

void Sprite::Draw() {
    SDL_RenderCopyF(renderer, texture, NULL, canvas);
}


void Sprite::SetCanvas(SDL_FRect *rect) {
    canvas = rect;
}

// void Sprite::SetRectSize(const Vector2 &value) {
//     canvas.w = value.x;
//     canvas.h = value.y;
// }

// void Sprite::SetRectPosition(const Vector2 &value) {
//     canvas.x = value.x;
//     canvas.y = value.y;
// }

// Vector2 Sprite::Centered() {
//     SDLRenderer *sdlRenderer = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
//     transform->position = sdlRenderer->WindowSize();
//     transform->position.x = (transform->position.x / 2.f) - (transform->size.x / 2.f);
//     transform->position.y = (transform->position.y / 2.f) - (transform->size.y / 2.f);

//     SetRectPosition();

//     return transform->position;
// }