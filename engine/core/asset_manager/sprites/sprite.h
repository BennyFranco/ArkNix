#ifndef SPRITE_H
#define SPRITE_H

#include "SDL_image.h"

#include "asset_manager.h"
#include "color.h"
#include "component.h"
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
        Sprite(const char *id, const char *filename);
        Sprite(const Sprite &other);
        Sprite(Sprite &&other);
        ~Sprite();

        Sprite &operator=(const Sprite &other);
        Sprite &operator=(Sprite &&other);

        bool Load(const char *filename) override;
        void Draw();
        void SetCanvas(SDL_FRect *rect);
        Vector2int GetSpriteSize();

    public:
        std::shared_ptr<SDL_Rect> srcCanvas;

    private:
        std::shared_ptr<SDL_Texture> texture;
        SDL_FRect *canvas;
        SDL_Renderer *renderer;
    };
}// namespace nim

#endif//SPRITE_H