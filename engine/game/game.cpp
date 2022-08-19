#include "game.h"
#include "asset_manager.h"
#include "input_locator.h"
#include "renderer_locator.h"
#include <functional>

using namespace nim;

void Game::Awake() {
    RendererLocator::Initialize();
    auto renderer = RendererLocator::GetRenderer();
    renderer->CreateWindow("Nim Engine", 800, 600);
    renderer->CreateRenderer(Color(0, 0, 0));
    InputLocator::Initialize();
    AssetManager::Instance().LoadAssets();
    running = true;
    std::function<void(bool)> callback = [=](bool stop) { ExitGameListener(stop); };
    InputLocator::GetInput()->onExitGameEvent.AddListener(std::move(callback));
}

void Game::Run() {
    // Awake();
    Update();
    // Quit();
}

void Game::Quit() {
    if (currentScene != nullptr)
        currentScene->Quit();
    RendererLocator::GetRenderer()->Quit();
}

void Game::Update() {
    int fps = 0;

    uint timestamp = SDL_GetTicks();

    while (running) {
        uint frameStart = SDL_GetTicks();
        InputLocator::GetInput()->Update();
        RendererLocator::GetRenderer()->Clear();

        if (currentScene != nullptr)
            currentScene->Update();

        RendererLocator::GetRenderer()->Update();
        uint frameEnd = SDL_GetTicks();
        uint frameDuration = frameEnd - frameStart;

        if ((frameEnd - timestamp) >= 1000) {
            RendererLocator::GetRenderer()->SetWindowTitle(std::string("Nim Engine - FPS: " + std::to_string(fps)));
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
}