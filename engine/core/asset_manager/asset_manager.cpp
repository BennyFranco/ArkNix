#include "asset_manager.h"
#include "sprite.h"

#include <filesystem>

AssetManager &AssetManager::Instance() {
    static std::unique_ptr<AssetManager> instance{new AssetManager()};
    return *instance;
}

void AssetManager::LoadAssets() {
    for (auto item: std::filesystem::directory_iterator(kAssetsPath)) {
        if (!item.is_regular_file()) continue;

        if (item.path().extension() == ".png") {
            const char *filename = item.path().c_str();
            const char *id = item.path().filename().replace_extension("").c_str();
            assets.emplace(id, std::make_unique<nim::Sprite>(filename));
        }
    }
}
