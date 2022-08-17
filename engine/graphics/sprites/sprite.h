#ifndef SPRITE_H
#define SPRITE_H

#include "SDL_image.h"
#include <string>

#include "asset_manager.h"
#include "color.h"
#include "vector2d.h"

// https://wiki.libsdl.org/SDL_CreateTexture
// https://wiki.libsdl.org/SDL_DestroyTexture
// https://wiki.libsdl.org/SDL_Rect
// https://wiki.libsdl.org/SDL_QueryTexture

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
        void SetSize(float w, float h);
        void SetPosition(float x, float y);
        void Centered();

    private:
        SDL_FRect canvas;
        SDL_Texture *texture;
        SDL_Renderer *renderer;
        Vector2 size;
        Vector2 position;

    private:
        void SetRectSize();
        void SetRectPosition();
    };
}// namespace nim

#endif//SPRITE_H