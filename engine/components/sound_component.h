#ifndef SOUND_COMPONENT_H
#define SOUND_COMPONENT_H

#include "component.h"
#include "sound.h"

namespace nim {

    class SoundComponent : public Component {
    public:
        SoundComponent();
        SoundComponent(std::string soundName);
        SoundComponent(const SoundComponent &other);
        SoundComponent(SoundComponent &&other);
        ~SoundComponent();

        SoundComponent &operator=(const SoundComponent &other);
        SoundComponent &operator=(SoundComponent &&other);

        //        void Init() override;
        //        void Update() override;
        //        void Quit() override;

        void Play();

    public:
        Sound sound;
    };

}// namespace nim

namespace YAML {
    template<>
    struct convert<nim::SoundComponent *> {
        static YAML::Node encode(const nim::SoundComponent *component) {
            YAML::Node node;
            //            node["name"] = component->name;
            //            node["atlas"] = component->sprite.id;
            //            node["animateOnInit"] = component->animateOnInit;
            //            node["offset"].push_back(component->xOffset);
            //            node["offset"].push_back(component->yOffset);
            //            node["frames"] = component->frames;
            return node;
        }
    };
    template<>
    struct convert<nim::SoundComponent> {
        static bool decode(const YAML::Node &node, nim::SoundComponent &component) {
            if (!node["name"] && !node["sound"]) return false;

            std::string soundName = node["sound"].as<std::string>();
            nim::SoundComponent sc(soundName);
            component = std::move(sc);

            return true;
        }
    };
}// namespace YAML

#endif//SOUND_COMPONENT_H
