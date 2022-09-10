#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "parser.h"
#include <string>
#include <vector>

namespace nim {
    class SceneManager {
    public:
        static void LoadSceneOrder();
        static std::string &NextScene();
        static std::string &FirstScene();
        static std::string &GetSceneByIndex(int index);

        static std::vector<std::string> scenes;
        static int currentIndex;
        static std::string kScenesOrder;
        static std::string kConfigPath;
    };
}// namespace nim

#endif//SCENE_MANAGER_H
