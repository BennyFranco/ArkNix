#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "component.h"
#include "sprite.h"

namespace nim {
    class AnimationComponent : public Component {
    public:
        AnimationComponent();
        AnimationComponent(std::string atlasName, bool animateOnInit);
        AnimationComponent(const &AnimationComponent other);
        AnimationComponent(AnimationComponent &&other);
        ~AnimationComponent();

        AnimationComponent &operator=(const &AnimationComponent other);
        AnimationComponent &operator=(const &&AnimationComponent other);

        void Init() override;
        void Update() override;
        void Quit() override;

        void Play();
        void Animate();
        void Stop();

    public:
        Sprite *sprite;// owned by AssetManager
        bool animateOnInit;
        int xOffset;
        int yOffset;

    private:
        bool animate;
    };
}// namespace nim
#endif