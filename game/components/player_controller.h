#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "component.h"
#include "input_locator.h"
#include "text_component.h"

namespace galaga {
    class PlayerController : public nim::Component {
    public:
        PlayerController();
        PlayerController(const PlayerController &controller);
        PlayerController(PlayerController &&controller);
        ~PlayerController();

        PlayerController &operator=(const PlayerController &controller);
        PlayerController &operator=(PlayerController &&controller);

        void Init() override;
        void Update() override;
        void Quit() override;

        void SetScoreLabel(long score);

    public:
        float velocity;

    private:
        nim::Input *input;// owned by input locator;
        nim::TextComponent *scoreLabel;
    };
}// namespace galaga

namespace YAML {
    template<>
    struct convert<galaga::PlayerController *> {
        static YAML::Node encode(const galaga::PlayerController *component) {
            YAML::Node node;
            node["name"] = component->name;
            node["velocity"] = component->velocity;
            return node;
        }
    };
    template<>
    struct convert<galaga::PlayerController> {
        static bool decode(const YAML::Node &node, galaga::PlayerController &component) {
            if (!node["name"]) return false;
            galaga::PlayerController cc;
            cc.velocity = node["velocity"].as<float>();
            component = std::move(cc);
            return true;
        }
    };
}// namespace YAML
#endif//PLAYER_CONTROLLER_H