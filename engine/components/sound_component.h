#ifndef SOUND_COMPONENT_H
#define SOUND_COMPONENT_H

#include "component.h"
#include "music.h"
#include "sound.h"

namespace nim {
    template<typename T>
    class SoundComponent : public Component {
    public:
        SoundComponent() {
            transform = nullptr;
            name = "SoundComponent";
        }

        SoundComponent(std::string assetName, bool play = false) {
            transform = nullptr;
            name = "SoundComponent";
            sound = AssetManager::Instance().Get<T>(assetName);
            autoplay = play;
        }

        SoundComponent(const SoundComponent &other) {
            name = other.name;
            transform = other.transform;
            sound = other.sound;
            autoplay = other.autoplay;
        }

        SoundComponent(SoundComponent &&other) noexcept {
            name = other.name;
            transform = other.transform;
            sound = std::move(other.sound);
            autoplay = other.autoplay;

            other.transform = nullptr;
            other.autoplay = false;
        }

        ~SoundComponent() override {
            transform = nullptr;
        }

        SoundComponent &operator=(const SoundComponent &other) {
            if (&other != this) {
                transform = nullptr;

                name = other.name;
                transform = other.transform;
                sound = other.sound;
                autoplay = other.autoplay;
            }

            return *this;
        }

        SoundComponent &operator=(SoundComponent &&other) {
            if (&other != this) {
                transform = nullptr;

                name = other.name;
                transform = other.transform;
                sound = std::move(other.sound);
                autoplay = other.autoplay;

                other.transform = nullptr;
                other.autoplay = false;
            }

            return *this;
        }

        void Init() override {
            if (autoplay) Play();
        }

        void Play() {
            sound.Play();
        }

        void Load(const std::string &id) {
            sound = AssetManager::Instance().Get<T>(id);
        }

    public:
        T sound;
        bool autoplay = false;
    };

}// namespace nim

namespace YAML {
    template<>
    struct convert<nim::SoundComponent<nim::Sound> *> {
        static YAML::Node encode(const nim::SoundComponent<nim::Sound> *component) {
            YAML::Node node;
            // TODO: Implement nim::SoundComponent<nim::Sound> Encoder
            return node;
        }
    };

    template<>
    struct convert<nim::SoundComponent<nim::Music> *> {
        static YAML::Node encode(const nim::SoundComponent<nim::Music> *component) {
            YAML::Node node;
            // TODO: Implement nim::SoundComponent<nim::Music> Encoder
            return node;
        }
    };
    template<>
    struct convert<nim::SoundComponent<nim::Sound>> {
        static bool decode(const YAML::Node &node, nim::SoundComponent<nim::Sound> &component) {
            if (!node["name"] || !node["sound"]) return false;

            auto soundName = node["sound"].as<std::string>();
            nim::SoundComponent<nim::Sound> sc(soundName);
            component = std::move(sc);

            return true;
        }
    };
    template<>
    struct convert<nim::SoundComponent<nim::Music>> {
        static bool decode(const YAML::Node &node, nim::SoundComponent<nim::Music> &component) {
            if (!node["name"] || !node["music"]) return false;

            auto soundName = node["music"].as<std::string>();
            bool autoplay = node["autoplay"].as<bool>();
            nim::SoundComponent<nim::Music> sc(soundName, autoplay);
            component = std::move(sc);

            return true;
        }
    };
}// namespace YAML

#endif//SOUND_COMPONENT_H
