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
    enum class SpriteFlip {
        None = 0,
        Horizontal,
        Vertical,
    };
    class Sprite : public Asset {
    public:
        Sprite();
        Sprite(const char *id, const char *filename);
        Sprite(const Sprite &other);
        Sprite(Sprite &&other) noexcept;
        ~Sprite();

        Sprite &operator=(const Sprite &other);
        Sprite &operator=(Sprite &&other) noexcept;

        void Draw();
        void SetFlip(SpriteFlip newFlip);
        void SetCanvas(SDL_FRect *rect);
        Vector2int GetSpriteSize();

    public:
        SDL_Rect srcCanvas{};

    private:
        std::shared_ptr<SDL_Texture> texture;
        SDL_FRect *canvas{};
        SDL_Renderer *renderer;
        SDL_RendererFlip flip;
    };
}// namespace nim

#endif//SPRITE_H