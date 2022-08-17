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
    class Sprite : public Asset, public Component {
    public:
        Sprite();
        Sprite(const char *filename);
        Sprite(const Sprite &other);
        Sprite(Sprite &&other);
        ~Sprite();

        Sprite &operator=(const Sprite &other);
        Sprite &operator=(Sprite &&other);

        bool Load(const char *filename) override;
        void Draw() override;
        void Size(Vector2 size) override;
        void Position(Vector2 position) override;
        void Size(float width, float height) override;
        void Position(float x, float y) override;
        void Centered();

    private:
        SDL_FRect canvas;
        SDL_Texture *texture;
        SDL_Renderer *renderer;
        // Vector2 size;
        // Vector2 position;

    private:
        void SetRectSize();
        void SetRectPosition();
    };
}// namespace nim

#endif//SPRITE_H