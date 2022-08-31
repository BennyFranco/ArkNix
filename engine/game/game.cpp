#include "game.h"
#include "asset_manager.h"
#include "collision_detector.h"
#include "input_locator.h"
#include "ntime.h"
#include "renderer_locator.h"
#include <filesystem>
#include <functional>

using namespace nim;

std::unique_ptr<Scene> Game::currentScene;

void Game::Awake() {
    RendererLocator::Initialize();
    auto renderer = RendererLocator::GetRenderer();
    renderer->CreateWindow(windowProperties.title, windowProperties.width, windowProperties.height);
    renderer->CreateRenderer(Color(0, 0, 0));
    InputLocator::Initialize();
    AssetManager::Instance().LoadAssets();
    running = true;
    std::function<void(bool)> callback = [=](bool stop) { ExitGameListener(stop); };
    InputLocator::GetInput()->onExitGameEvent.AddListener(std::move(callback));
}

void Game::Run() {
    Update();
}

void Game::Quit() {
    if (currentScene != nullptr) {
        currentScene->Quit();
        currentScene.reset();
    }

    AssetManager::Instance().Quit();
    RendererLocator::GetRenderer()->Quit();
}

void Game::Update() {
    int fps = 0;

    uint timestamp = NimTime::Instance().GetTicks();

    while (running) {
        uint frameStart = NimTime::Instance().GetTicks();
        InputLocator::GetInput()->Update();
        RendererLocator::GetRenderer()->Clear();

#ifdef EDITOR_DEBUG
        if (InputLocator::GetInput()->GetKey(Key::R)) {
            ReloadScene();
        }
#endif

        if (currentScene != nullptr) {
            currentScene->RemoveDirtyObjects();
            CollisionDetector::Instance().Update(currentScene->GetSceneData()->gameObjects);
            currentScene->Update();
        }

        RendererLocator::GetRenderer()->Update();

        uint frameEnd = NimTime::Instance().GetTicks();
        uint frameDuration = frameEnd - frameStart;

        if ((frameEnd - timestamp) >= 1000) {
            RendererLocator::GetRenderer()->SetWindowTitle(std::string(windowProperties.title + " - FPS: " + std::to_string(fps)));
            fps = 0;
            timestamp = frameEnd;
        }

        if (frameDuration < kDelayTime) {
            SDL_Delay(kDelayTime - frameDuration);
        }
        fps++;
    }
}

void Game::ExitGameListener(bool stop) {
    running = stop;
}

void Game::LoadScene(std::string sceneName) {
    currentScene = std::move(Scene::LoadScene(sceneName));
    if (currentScene != nullptr)
        currentScene->Init();
}

void Game::ReloadScene() {
    std::string currentName = currentScene->Name();
    const std::filesystem::path path = currentName;
    if (!path.has_extension()) {
        currentName.append(".yaml");
    }

    currentScene.reset();
    LoadScene(currentName);
}

GameObject *Game::AddGameObject(GameObject &&gameObject) {
    return currentScene->AddGameObject(std::move(gameObject));
}

void Game::RemoveGameObject(const std::string &name) {
    currentScene->RemoveGameObject(name);
}

GameObject *Game::Find(std::string name) {
    auto sceneData = currentScene->GetSceneData();
    auto result = std::find_if(sceneData->gameObjects.begin(), sceneData->gameObjects.end(), [name](GameObject go) {
        return go.name == name;
    });

    return &*result;
}