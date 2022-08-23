#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H

#include "component.h"
#include "input_locator.h"

namespace nim {
    class CharacterController : public Component {
    public:
        CharacterController();
        CharacterController(const CharacterController &controller);
        CharacterController(CharacterController &&controller);
        ~CharacterController() {}

        CharacterController &operator=(const CharacterController &controller);
        CharacterController &operator=(CharacterController &&controller);

        virtual void Update() override;

    private:
        Input *input;// owned by input locator;
    };
}// namespace nim
namespace YAML {
    template<>
    struct convert<nim::CharacterController *> {
        static YAML::Node encode(const nim::CharacterController *component) {
            YAML::Node node;
            node["name"] = component->name;
            return node;
        }
    };
    template<>
    struct convert<nim::CharacterController> {
        static bool decode(const YAML::Node &node, nim::CharacterController &component) {
            if (!node["name"]) return false;
            nim::CharacterController cc;
            component = std::move(cc);
            return true;
        }
    };
}// namespace YAML
#endif// CHARACTER_CONTROLLER_H