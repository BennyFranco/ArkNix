#ifndef FONT_H
#define FONT_H

#include "SDL_ttf.h"
#include "asset_manager.h"
#include "types.h"
#include <memory>

namespace nim {
    class Font : public Asset {
    public:
        Font();
        Font(const char *id, const char *filename);
        Font(const Font &other);
        Font(Font &&other);
        ~Font();

        Font &operator=(const Font &other);
        Font &operator=(Font &&other);

        bool Load(const char *filename) override;
        void Draw(SDL_Texture *texture, SDL_Rect source, SDL_Rect destination);
        TTF_Font *Get() { return font.get(); }

    private:
        std::shared_ptr<TTF_Font> font;
        SDL_Renderer *renderer;
    };
}// namespace nim
#endif//FONT_H