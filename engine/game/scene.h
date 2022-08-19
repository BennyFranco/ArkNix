#ifndef SCENE_H
#define SCENE_H

#include "asset_manager.h"
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
        Scene();
        Scene(const Scene &otherScene);
        Scene(Scene &&otherScene);
        ~Scene();

        Scene &operator=(const Scene &otherScene);
        Scene &operator=(Scene &&otherScene);

        void Init() override;
        void Update() override;
        void Quit() override;
        void Save(std::string filename = "");
        std::string Name() const { return sceneData->name; }
        SceneData *GetData() const { return sceneData.get(); }

        static std::unique_ptr<Scene> LoadScene(std::string sceneName);

    private:
        std::unique_ptr<SceneData> sceneData;
        const uint fileVersion = 1;
    };
}// namespace nim

namespace YAML {
    template<>
    struct convert<nim::SceneData> {
        static YAML::Node encode(const nim::SceneData &sd) {
            YAML::Node node;
            node["name"] = sd.name;
            node["gameObjects"] = sd.gameObjects;
            return node;
        }

        static bool decode(const YAML::Node &node, nim::SceneData &sd) {
            if (!node["name"]) return false;
            sd.name = node["name"].as<std::string>();

            std::vector<nim::GameObject> gameObjects;
            // for (auto i = node["gameObjects"].begin(); i != node["gameObjects"].end(); i++)
            for (int i = 0; i < node["gameObjects"].size(); i++) {
                gameObjects.emplace_back(node["gameObjects"][i].as<nim::GameObject>());
            }

            sd.gameObjects = std::move(gameObjects);
            return true;
        }
    };
}// namespace YAML
#endif//SCENE_H