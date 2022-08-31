#ifndef GAME_H
#define GAME_H

#include "scene.h"

#include <iostream>
#include <memory>

namespace nim {
    struct WindowProperties {
        int width = 800;
        int height = 600;
        std::string title = "Nim Engine";
    };

    class Game {
    public:
        virtual void Awake();
        virtual void Run();
        virtual void Quit();

        virtual void LoadScene(std::string sceneName);
        virtual void ReloadScene();

        static GameObject *AddGameObject(GameObject &&gameObject);
        static void RemoveGameObject(const std::string& name);
        static GameObject *Find(std::string name);

    private:
        void Update();
        void ExitGameListener(bool);

    public:
    protected:
        WindowProperties windowProperties;
        static std::unique_ptr<Scene> currentScene;


    private:
        bool running;
        const uint kTargetFps = 60;
        const uint kDelayTime = 1000.f / kTargetFps;
    };
}// namespace nim
#endif// GAME_H