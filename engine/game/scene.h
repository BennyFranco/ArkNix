#ifndef SCENE_H
#define SCENE_H

#include "entity.h"
#include "game_object.h"

#include <memory>
#include <string>
#include <vector>

namespace nim {
    struct SceneData {
        std::string name;
        std::vector<GameObject> gameObjects;
    };

    class Scene : public Entity {
    public:
        void Init() override;
        void Update() override;
        void Quit() override;
        std::string Name() const { return sceneData->name; }

    private:
        std::unique_ptr<SceneData> sceneData;
    };
}// namespace nim
#endif//SCENE_H