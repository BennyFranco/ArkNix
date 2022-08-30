#include "asset_manager.h"
#include "color.h"
#include "font.h"
#include "sprite.h"

#include <filesystem>
#include <iostream>

using namespace nim;

AssetManager::AssetManager() {}

AssetManager &AssetManager::Instance() {
    static std::unique_ptr<AssetManager> instance{new AssetManager()};
    return *instance;
}

void AssetManager::LoadAssets() {
    for (auto item: std::filesystem::directory_iterator(kAssetsPath)) {
        if (!item.is_regular_file()) continue;
        // TODO: define more supported formats
        std::string extension = item.path().extension();
        std::string filename = item.path().string();
        std::string id = item.path().filename().replace_extension("").string();

        if (extension == ".png") {
            assets.emplace(id, std::make_shared<nim::Sprite>(id.c_str(), filename.c_str()));
            std::cout << "[AssetManager] Asset loaded with id = " << id << "\n";
        } else if (extension == ".ttf") {
            assets.emplace(id, std::make_shared<nim::Font>(id.c_str(), filename.c_str()));
            std::cout << "[AssetManager] Asset loaded with id = " << id << "\n";
        }
    }
}

void AssetManager::Quit() {
    assets.clear();
}
