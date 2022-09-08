#include "font.h"
#include "renderer_locator.h"

using namespace nim;

Font::Font() {
    SDLRenderer *rend = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
}

Font::Font(const char *id, const char *filename) {
    SDLRenderer *rend = static_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
    this->id = id;
    TTF_Font *tFont = TTF_OpenFont(filename, defaultSize);
    font.reset(tFont, [](TTF_Font *f) { TTF_CloseFont(f); });
    this->filename = filename;
}

Font::Font(const Font &other) {
    filename = other.filename;
    font = other.font;
}

Font::Font(Font &&other) {
    filename = other.filename;
    font = std::move(other.font);
    other.filename = nullptr;
}

Font::~Font() = default;

Font &Font::operator=(const Font &other) {
    if (&other == this) return *this;
    filename = other.filename;
    font = other.font;
    return *this;
}

Font &Font::operator=(Font &&other) {
    filename = other.filename;
    font = std::move(other.font);
    return *this;
}

void Font::Draw(SDL_Texture *texture, SDL_Rect source, SDL_Rect destination) {
    SDL_RenderCopyEx(renderer, texture, &source, &destination, 0, 0, SDL_FLIP_NONE);
}
void Font::SetSize(int size) {
    TTF_SetFontSize(font.get(), size);
}
