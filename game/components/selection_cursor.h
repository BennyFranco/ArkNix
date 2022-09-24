#ifndef SELECTION_CURSOR_H
#define SELECTION_CURSOR_H

#include "color.h"
#include "component.h"
#include "input.h"
#include "sound_component.h"

namespace galaga {
    class SelectionCursor : public nim::Component {
    public:
        SelectionCursor();
        SelectionCursor(std::vector<std::string> elements);
        SelectionCursor(const SelectionCursor &other);
        SelectionCursor(SelectionCursor &&other) noexcept;
        ~SelectionCursor() override;

        SelectionCursor &operator=(const SelectionCursor &other);
        SelectionCursor &operator=(SelectionCursor &&other) noexcept;

        void Init() override;
        void Update() override;

    private:
        void NextElement(int newIndex);

    private:
        nim::SoundComponent<nim::Sound> *select{};
        nim::SoundComponent<nim::Sound> *startLevel{};
        std::vector<std::string> elementNames;
        std::vector<nim::GameObject *> elementReferences;
        nim::Input *input;
        nim::Color colorCache;
        int currentIndex = 0;
        float channelValue = 0;
        float t = 0.1f;
        bool prepareForTransition = false;
    };
}// namespace galaga

namespace YAML {
    template<>
    struct convert<galaga::SelectionCursor *> {
        static YAML::Node encode(const galaga::SelectionCursor *component) {
            YAML::Node node;
            // TODO: Define encoder for galaga::SelectionCursor *
            return node;
        }
    };
    template<>
    struct convert<galaga::SelectionCursor> {
        static bool decode(const YAML::Node &node, galaga::SelectionCursor &component) {
            if (!node["name"] || !node["items"]) return false;

            std::vector<std::string> items;
            for (auto item: node["items"])
                items.emplace_back(item.as<std::string>());

            galaga::SelectionCursor cursor{items};
            component = std::move(cursor);
            return true;
        }
    };
}// namespace YAML

#endif//SELECTION_CURSOR_H
