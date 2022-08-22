#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "component.h"
#include "sprite.h"

namespace nim {
    class AnimationComponent : public Component {
    public:
        AnimationComponent();
        AnimationComponent(std::string atlasName, bool animateOnInit);
        AnimationComponent(const AnimationComponent &other);
        AnimationComponent(AnimationComponent &&other);
        ~AnimationComponent();

        AnimationComponent &operator=(const AnimationComponent &other);
        AnimationComponent &operator=(AnimationComponent &&other);

        void Init() override;
        void Update() override;
        void Quit() override;
        void SetTransform(Transform *transform) override;

        void Play();
        void Animate();
        void Stop();

    public:
        Sprite *sprite;// owned by AssetManager
        bool animateOnInit;
        int xOffset;
        int yOffset;
        uint frames;

    private:
        bool animate;
    };
}// namespace nim

namespace YAML {
    template<>
    struct convert<nim::AnimationComponent *> {
        static YAML::Node encode(const nim::AnimationComponent *component) {
            YAML::Node node;
            node["type"] = component->type;
            node["name"] = component->name;
            node["atlas"] = component->sprite->id;
            node["animateOnInit"] = component->animateOnInit;
            node["offset"].push_back(component->xOffset);
            node["offset"].push_back(component->yOffset);
            node["frames"] = component->frames;
            return node;
        }
    };
    template<>
    struct convert<nim::AnimationComponent> {
        static bool decode(const YAML::Node &node, nim::AnimationComponent &component) {
            if (!node["name"] && !node["atlas"]) return false;

            std::string atlasName = node["atlas"].as<std::string>();
            bool animate = node["animateOnInit"].as<bool>();
            int xOffset = node["offset"][0].as<int>();
            int yOffset = node["offset"][1].as<int>();
            uint frames = node["frames"].as<uint>();

            nim::AnimationComponent sc(atlasName, animate);
            sc.xOffset = xOffset;
            sc.yOffset = yOffset;
            sc.frames = frames;
            component = std::move(sc);

            return true;
        }
    };
}// namespace YAML
#endif