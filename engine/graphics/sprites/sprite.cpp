#include "sprites/sprite.h"
#include "renderer_locator.h"

#include <iostream>

using namespace nim;

Sprite::Sprite() {
    std::cout << "Sprite Constructor" << std::endl;
    SDLRenderer *rend = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();

    texture = NULL;
}

Sprite::Sprite(const char *filename) {
    std::cout << "Sprite Constructor With Filename" << std::endl;

    SDLRenderer *rend = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
    Load(filename);
}

Sprite::~Sprite() {
    std::cout << "Sprite Destructor" << std::endl;

    if (texture != NULL)
        SDL_DestroyTexture(texture);
}

Sprite::Sprite(const Sprite &other) {
    std::cout << "Sprite Copy Constructor" << std::endl;

    filename = other.filename;
    texture = other.texture;
}

Sprite::Sprite(Sprite &&other) {
    std::cout << "Sprite Move Constructor" << std::endl;

    filename = other.filename;
    texture = other.texture;

    other.filename = nullptr;
    other.texture = NULL;
}

Sprite &Sprite::operator=(const Sprite &other) {
    std::cout << "Sprite Copy Operator" << std::endl;

    if (&other == this) return *this;

    SDL_DestroyTexture(texture);
    filename = nullptr;

    filename = other.filename;
    texture = other.texture;

    return *this;
}

Sprite &Sprite::operator=(Sprite &&other) {
    std::cout << "Sprite Move Operator" << std::endl;
    if (&other == this) return *this;

    // filename = other.filename;
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

    return true;
}

void Sprite::Draw() {
    SDL_RenderCopy(renderer, texture, 0, 0);
}