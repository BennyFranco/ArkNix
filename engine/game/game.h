#ifndef GAME_H
#define GAME_H

#include "scene.h"

#include <iostream>
#include <memory>

namespace nim {
    class Game {
    public:
        virtual void Awake();
        virtual void Run();
        virtual void Quit();

    private:
        void Update();
        void ExitGameListener(bool);

    private:
        bool running;
        const uint kTargetFps = 60;
        const uint kDelayTime = 1000.f / kTargetFps;
        std::unique_ptr<Scene> currentScene;
    };
}// namespace nim
#endif// GAME_H