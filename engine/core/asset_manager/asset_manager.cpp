#include "asset_manager.h"
#include "color.h"
#include "sprite.h"

#include <filesystem>
#include <iostream>

using namespace nim;

AssetManager::AssetManager() {
}

AssetManager &AssetManager::Instance() {
    static std::unique_ptr<AssetManager> instance{new AssetManager()};
    return *instance;
}

void AssetManager::LoadAssets() {
    for (auto item: std::filesystem::directory_iterator(kAssetsPath)) {
        if (!item.is_regular_file()) continue;
        // TODO: define more supported formats
        if (item.path().extension() == ".png") {
            std::string filename = item.path().c_str();
            std::string id = item.path().filename().replace_extension("").c_str();
            assets.emplace(id, std::make_shared<nim::Sprite>(id.c_str(), filename.c_str()));
            std::cout << "[AssetManager] Asset loaded with id = " << id << "\n";
        }
    }
}
