#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include "color.h"
#include "component.h"
#include "font.h"

namespace nim {
    class TextComponent : public Component {
    public:
        TextComponent();
        TextComponent(const std::string& fontName);
        TextComponent(const std::string &fontName, int size);
        TextComponent(const TextComponent &other);
        TextComponent(TextComponent &&other) noexcept;
        ~TextComponent() override;

        TextComponent &operator=(const TextComponent &other);
        TextComponent &operator=(TextComponent &&other) noexcept;

        void Init() override;
        void Update() override;
        void Quit() override;
        void SetTransform(Transform *transform) override;

        void Text(std::string text);
        inline std::string Text() const { return text; }
        void SetColor(const Color &newColor);
        inline Color GetColor() const { return fontColor; }

    private:
        void CreateTexture();

    private:
        Font font;
        std::shared_ptr<SDL_Texture> texture;
        SDL_Rect srcCanvas{};
        SDL_Rect destCanvas{};
        SDL_Renderer *renderer;
        std::string text;
        Color fontColor;
    };
}// namespace nim
namespace YAML {
    template<>
    struct convert<nim::TextComponent *> {
        static YAML::Node encode(const nim::TextComponent *component) {
            YAML::Node node;
            // node["name"] = component->name;
            // node["atlas"] = component->sprite.id;
            // node["animateOnInit"] = component->animateOnInit;
            // node["offset"].push_back(component->xOffset);
            // node["offset"].push_back(component->yOffset);
            // node["frames"] = component->frames;
            return node;
        }
    };
    template<>
    struct convert<nim::TextComponent> {
        static bool decode(const YAML::Node &node, nim::TextComponent &component) {
            if (!node["name"] && !node["font"]) return false;

            auto fontName = node["font"].as<std::string>();
            auto text = node["text"].as<std::string>();
            auto color = node["color"].as<nim::Color>();

            if (node["size"]) {
                auto size = node["size"].as<int>();
                nim::TextComponent sc(fontName, size);
                sc.SetColor(color);
                sc.Text(text);
                component = std::move(sc);
            } else {
                nim::TextComponent sc(fontName);
                sc.SetColor(color);
                sc.Text(text);
                component = std::move(sc);
            }

            return true;
        }
    };
}// namespace YAML
#endif// TEXT_COMPONENT_H