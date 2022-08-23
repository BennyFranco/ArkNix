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
        void LoadAssets();
        template<typename T>
        T Get(std::string id) {
            if (assets.find(id) == assets.end()) {
                // TODO: Create a logger
                std::cout << "[AssetManager] The asset with id: '" + id + "' doesn't exist!" << std::endl;
                auto value = dynamic_cast<T *>(assets["default"].get());
                return *value;
            }
            auto value = dynamic_cast<T *>(assets[id].get());
            return *value;
        }

    private:
        AssetManager();
        std::map<std::string, std::shared_ptr<nim::Asset>> assets;
#ifdef EDITOR_DEBUG
        const char *kAssetsPath = "../assets/";
#else
        const char *kAssetsPath = "assets/";
#endif
    };
}// namespace nim
#endif//ASSET_MANAGER_H