#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <string>

namespace nim {
    class Asset {
    public:
        virtual bool Load(const char *filename) = 0;
        virtual ~Asset() = default;

    protected:
        std::string filename;
    };
}// namespace nim

#endif//ASSET_H