#include "sprite.h"
#include "renderer_locator.h"

using namespace nim;

Sprite::Sprite() {
    // std::cout << "Sprite Constructor" << std::endl;
    SDLRenderer *rend = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
    texture = NULL;
    name = "SpriteComponent";
    transform = nullptr;
}

Sprite::Sprite(const char *filename) {
    // std::cout << "Sprite Constructor With Filename" << std::endl;

    name = "SpriteComponent";
    SDLRenderer *rend = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
    Load(filename);
    transform = nullptr;
}

Sprite::~Sprite() {
    // std::cout << "Sprite Destructor" << std::endl;

    if (texture != NULL)
        SDL_DestroyTexture(texture);
}

Sprite::Sprite(const Sprite &other) {
    // std::cout << "Sprite Copy Constructor" << std::endl;

    filename = other.filename;
    texture = other.texture;
    name = other.name;
    transform = other.transform;
}

Sprite::Sprite(Sprite &&other) {
    // std::cout << "Sprite Move Constructor" << std::endl;

    filename = other.filename;
    texture = other.texture;
    name = other.name;
    transform = other.transform;

    other.filename = nullptr;
    other.texture = NULL;
    other.name = nullptr;
    other.transform = nullptr;
}

Sprite &Sprite::operator=(const Sprite &other) {
    // std::cout << "Sprite Copy Operator" << std::endl;

    if (&other == this) return *this;

    SDL_DestroyTexture(texture);

    filename = other.filename;
    texture = other.texture;
    name = other.name;
    transform = other.transform;

    return *this;
}

Sprite &Sprite::operator=(Sprite &&other) {
    if (&other == this) return *this;

    SDL_DestroyTexture(texture);

    filename = other.filename;
    texture = other.texture;
    name = other.name;
    transform = other.transform;

    other.filename = nullptr;
    other.texture = NULL;
    other.name = nullptr;
    transform = nullptr;

    return *this;
}

bool Sprite::Load(const char *filename) {
    SDL_Surface *loadingSurface = IMG_Load(filename);
    texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
    this->filename = filename;

    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    // SetRectPosition();
    // SetRectSize();

    return true;
}

void Sprite::Draw() {
    SetRectPosition();
    SetRectSize();
    SDL_RenderCopyF(renderer, texture, NULL, &canvas);
}

void Sprite::SetRectSize() {
    canvas.w = transform->size.w();
    canvas.h = transform->size.h();
}

void Sprite::SetRectPosition() {
    canvas.x = transform->position.x;
    canvas.y = transform->position.y;
}

Vector2 Sprite::Centered() {
    SDLRenderer *sdlRenderer = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    transform->position = sdlRenderer->WindowSize();
    transform->position.x = (transform->position.x / 2.f) - (transform->size.x / 2.f);
    transform->position.y = (transform->position.y / 2.f) - (transform->size.y / 2.f);

    SetRectPosition();

    return transform->position;
}