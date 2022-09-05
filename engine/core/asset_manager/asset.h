#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <string>

namespace nim {
    class Asset {
    public:
        virtual ~Asset() = default;

    public:
        std::string filename;
        std::string id;
    };
}// namespace nim

#endif//ASSET_H