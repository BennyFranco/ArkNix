#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <memory>
#include <string>

#include "asset.h"

// https://gameprogrammingpatterns.com/singleton.html
namespace nim {
    class AssetManager {
    public:
        static AssetManager &Instance();
        void LoadAssets(std::string &&directory = kAssetsPath);
        template<typename T>
        T LoadAsset(const std::string &filename, const std::string &id) {
            if (assets.find(id) != assets.end()) {
                return *dynamic_cast<T *>(assets[id].get());
            }
            auto asset = std::make_shared<T>(id.c_str(), filename.c_str());
            assets.emplace(id, asset);
            return *asset;
        }
        template<typename T>
        T Get(const std::string &id) {
            if (assets.find(id) == assets.end()) {
                // TODO: Create a logger
                std::cout << "[AssetManager] The asset with id: '" + id + "' doesn't exist!" << std::endl;
                auto value = dynamic_cast<T *>(assets["default"].get());
                return *value;
            }
            auto value = dynamic_cast<T *>(assets[id].get());
            return *value;
        }
        std::string GetFilename(const std::string &id);
        void Quit();

    private:
        AssetManager() = default;
        std::map<std::string, std::shared_ptr<nim::Asset>> assets;
        inline static const char *kAssetsPath = "../assets/";
    };
}// namespace nim
#endif//ASSET_MANAGER_H