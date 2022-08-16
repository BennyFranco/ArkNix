#ifndef RENDERER_H
#define RENDERER_H

#include <string>

#include "entity.h"

struct Color {
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;

    Color(uint8_t r, uint8_t g, uint8_t b) {
        R = r;
        G = g;
        B = b;
        A = 255;
    }

    Color(int r, int g, int b, int a) {
        R = r;
        G = g;
        B = b;
        A = a;
    }
};

class Renderer : public Entity {
public:
    virtual void CreateWindow(std::string title, int x_position, int y_position, int width, int height, uint flags) = 0;
    virtual void CreateRenderer(Color color) = 0;
    virtual void Clear() = 0;
};

#endif// RENDERER_H