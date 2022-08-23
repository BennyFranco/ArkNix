#ifndef DEBUG_COMPONENT_H
#define DEBUG_COMPONENT_H

#include "component.h"
#include "input_locator.h"

namespace nim {
    class DebugComponent : public Component {
    public:
        void Awake() {
            name = "DebugComponent";
            input = InputLocator::GetInput();
        }
        void Update() override {
            // if (input->GetKeyDown(Key::UP)) {
            //     std::cout << "Position: " << transform->position.x << "\n";
            // }
            // if (input->GetKeyDown(Key::DOWN)) {
            //     std::cout << "Position: " << transform->position << "\n";
            // }
            // if (input->GetKeyDown(Key::LEFT)) {
            //     std::cout << "Position: " << transform->position << "\n";
            // }
            // if (input->GetKeyDown(Key::RIGHT)) {
            //     std::cout << "Position: " << transform->position << "\n";
            // }
            std::cout << "Position: X:" << transform->position.x << " Y: " << transform->position.y << "\n";
        }

    private:
        Input *input;// owned by input locator;
    };
}// namespace nim
#endif//DEBUG_COMPONENT_H