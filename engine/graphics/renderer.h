#ifndef RENDERER_H
#define RENDERER_H

#include <string>

#include "color.h"
#include "entity.h"

namespace nim {
    class Renderer : public Entity {
    public:
        virtual void CreateWindow(std::string title, int x_position, int y_position, int width, int height, uint flags) = 0;
        virtual void CreateRenderer(Color color) = 0;
        virtual void Clear() = 0;
    };
}// namespace nim
#endif// RENDERER_H