#include "font.h"
#include "renderer_locator.h"

using namespace nim;

Font::Font() {
    auto *rend = dynamic_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
}

Font::Font(const char *id, const char *filename) {
    auto *rend = dynamic_cast<SDLRenderer *>(RendererLocator::GetRenderer());
    renderer = rend->Renderer();
    this->id = id;
    TTF_Font *tFont = TTF_OpenFont(filename, defaultSize);
    font.reset(tFont, [](TTF_Font *f) { TTF_CloseFont(f); });
    this->filename = filename;
}

Font::Font(const Font &other) {
    filename = other.filename;
    font = other.font;
    renderer = other.renderer;
}

Font::Font(Font &&other) noexcept {
    filename = other.filename;
    font = std::move(other.font);
    renderer = other.renderer;
    other.filename = nullptr;
    other.renderer = nullptr;
}

Font::~Font() = default;

Font &Font::operator=(const Font &other) {
    if (&other == this) return *this;
    filename = other.filename;
    font = other.font;
    renderer = other.renderer;
    return *this;
}

Font &Font::operator=(Font &&other) noexcept {
    filename = other.filename;
    font = std::move(other.font);
    renderer = other.renderer;
    other.filename = nullptr;
    other.renderer = nullptr;
    return *this;
}

void Font::Draw(SDL_Texture *texture, SDL_Rect source, SDL_Rect destination) {
    SDL_RenderCopyEx(renderer, texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
}
void Font::SetSize(int size) {
    TTF_SetFontSize(font.get(), size);
}
