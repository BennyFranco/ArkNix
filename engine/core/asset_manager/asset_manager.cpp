#include "asset_manager.h"
#include "font.h"
#include "music.h"
#include "sound.h"
#include "sprite.h"

#if __GNUC__ >= 8 || _MSC_VER >= 1920 || __APPLE__
#include <filesystem>
#else
#include <dirent.h>
#include <unistd.h>
#endif
#include <iostream>

using namespace nim;

AssetManager &AssetManager::Instance() {
    static std::unique_ptr<AssetManager> instance{new AssetManager()};
    return *instance;
}

void AssetManager::LoadAssets(std::string &&directory) {
#if __GNUC__ >= 8 || _MSC_VER >= 1920 || __APPLE__

    for (auto &item: std::filesystem::directory_iterator(directory)) {
        if (item.is_directory())
            LoadAssets(item.path().string());

        if (!item.is_regular_file()) continue;

        std::string extension = item.path().extension().string();
        std::string filename = item.path().string();
        std::string id = item.path().filename().replace_extension("").string();

        // TODO: define more supported formats
        if (extension == ".png") {
            assets.emplace(id, std::make_shared<nim::Sprite>(id.c_str(), filename.c_str()));
            std::cout << "[AssetManager] Asset loaded with id = " << id << "\n";
        } else if (extension == ".ttf") {
            assets.emplace(id, std::make_shared<nim::Font>(id.c_str(), filename.c_str()));
            std::cout << "[AssetManager] Asset loaded with id = " << id << "\n";
        } else if (extension == ".wav") {
            assets.emplace(id, std::make_shared<nim::Sound>(id.c_str(), filename.c_str()));
            std::cout << "[AssetManager] Asset loaded with id = " << id << "\n";
        } else if (extension == ".mp3") {
            assets.emplace(id, std::make_shared<nim::Music>(id.c_str(), filename.c_str()));
            std::cout << "[AssetManager] Asset loaded with id = " << id << "\n";
        }
    }
#else
    // TODO: Add workaround here.
#endif
}

void AssetManager::Quit() {
    assets.clear();
}
std::string AssetManager::GetFilename(const std::string &id) {
    if (assets.find(id) == assets.end()) {
        std::cout << "[AssetManager] The asset with id: '" + id + "' doesn't exist!" << std::endl;
        return {};
    }
    auto result = assets[id].get();
    return result->filename;
}
