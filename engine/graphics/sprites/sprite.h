#ifndef SPRITE_H
#define SPRITE_H

#include "SDL_image.h"
#include <string>

#include "asset_manager.h"
#include "color.h"

// https://wiki.libsdl.org/SDL_CreateTexture
// https://wiki.libsdl.org/SDL_DestroyTexture
// https://wiki.libsdl.org/SDL_Rect

// TODO: Create macro for enable only SDL dependencies
namespace nim {
    class Sprite : public Asset {
    public:
        Sprite();
        Sprite(const char *filename);
        Sprite(const Sprite &other);
        Sprite(Sprite &&other);
        ~Sprite();

        Sprite &operator=(const Sprite &other);
        Sprite &operator=(Sprite &&other);

        bool Load(const char *filename) override;
        void Draw();

    private:
        SDL_Texture *texture;
        SDL_Renderer *renderer;
    };
}// namespace nim

#endif//SPRITE_H