#ifndef RENDERER_H
#define RENDERER_H

#include <string>

#include "color.h"
#include "types.h"
#include "vector2d.h"

namespace nim {
    class Renderer {
    public:
        virtual ~Renderer() = default;

        virtual void CreateWindow(std::string title, int x_position,
                                  int y_position, int width, int height, uint flags) = 0;
        virtual void CreateWindow(std::string title, int width, int height) = 0;
        virtual void SetWindowTitle(std::string title) = 0;
        virtual void CreateRenderer(Color color) = 0;
        virtual void Clear() = 0;
        virtual int Width() = 0;
        virtual int Height() = 0;
        virtual Vector2int WindowSize() = 0;

        virtual void Init() = 0;
        virtual void Update() = 0;
        virtual void Quit() = 0;
    };
}// namespace nim
#endif// RENDERER_H