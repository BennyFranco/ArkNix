#ifndef RENDERER_H
#define RENDERER_H

#include <string>

#include "color.h"
#include "entity.h"
#include "vector2d.h"

namespace nim {
    class Renderer : public Entity {
    public:
        virtual void CreateWindow(std::string title, int x_position,
                                  int y_position, int width, int height, uint flags) = 0;
        virtual void CreateWindow(std::string title, int width, int height) = 0;
        virtual void SetWindowTitle(std::string title) = 0;
        virtual void CreateRenderer(Color color) = 0;
        virtual void Clear() = 0;
        virtual int Width() = 0;
        virtual int Height() = 0;
        virtual Vector2 WindowSize() = 0;
    };
}// namespace nim
#endif// RENDERER_H