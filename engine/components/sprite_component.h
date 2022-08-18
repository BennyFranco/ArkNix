#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "component.h"
#include "sprite.h"

namespace nim {
    class SpriteComponent : public Component {
    public:
        SpriteComponent();
        SpriteComponent(const char *assetName);
        SpriteComponent(const char *name, const char *assetName);
        SpriteComponent(Sprite *sprite);
        SpriteComponent(const char *name, Sprite *sprite);
        SpriteComponent(const SpriteComponent &other);
        SpriteComponent(SpriteComponent &&other);
        ~SpriteComponent();

        SpriteComponent &operator=(const SpriteComponent &other);
        SpriteComponent &operator=(SpriteComponent &&other);

        void Draw() override;
        void SetTransform(Transform *transform) override;

    public:
        Sprite *sprite; // owned by AssetManager
    };
}// namespace nim
#endif//SPRITE_COMPONENT_H