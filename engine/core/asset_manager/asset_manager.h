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
        T *Get(std::string id) {
            if (assets.find(id) == assets.end()) {
                // throw std::runtime_error("[AssetManager] The asset with id: '" + id + "' doesn't exist!");
                return static_cast<T *>(assets["default"].get());
            }
            return static_cast<T *>(assets[id].get());
        }

    private:
        AssetManager();
        std::map<std::string, std::unique_ptr<nim::Asset>> assets;
#ifdef EDITOR_DEBUG
        const char *kAssetsPath = "../assets/";
#else
        const char *kAssetsPath = "assets/";
#endif
    };
}// namespace nim
#endif//ASSET_MANAGER_H