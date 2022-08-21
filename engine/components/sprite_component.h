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

        void Update() override;
        void SetTransform(Transform *transform) override;

    public:
        Sprite *sprite;// owned by AssetManager
    };
}// namespace nim

namespace YAML {
    template<>
    struct convert<nim::SpriteComponent *> {
        static YAML::Node encode(const nim::SpriteComponent *component) {
            YAML::Node node;
            node["type"] = (int) component->type;
            node["name"] = component->name;
            node["asset"] = component->sprite->id;
            return node;
        }
    };
    template<>
    struct convert<nim::SpriteComponent> {
        static bool decode(const YAML::Node &node, nim::SpriteComponent &component) {
            if (!node["name"] && !node["asset"]) return false;
            nim::SpriteComponent sc(node["asset"].as<std::string>().c_str());
            component = std::move(sc);
            return true;
        }
    };
}// namespace YAML
#endif//SPRITE_COMPONENT_H