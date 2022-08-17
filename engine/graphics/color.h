#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

namespace nim {
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
}// namespace nim
#endif//COLOR_H