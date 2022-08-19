#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <string>

namespace nim {
    class Asset {
    public:
        virtual bool Load(const char *filename) = 0;
        virtual ~Asset() = default;

    public:
        std::string filename;
        std::string id;
    };
}// namespace nim

#endif//ASSET_H