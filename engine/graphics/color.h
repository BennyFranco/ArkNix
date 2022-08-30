#ifndef COLOR_H
#define COLOR_H

#include "yaml-cpp/yaml.h"
#include <SDL.h>
#include <cstdint>

namespace nim {
    struct Color {
        uint8_t R;
        uint8_t G;
        uint8_t B;
        uint8_t A;

        Color() {
            R = 0;
            G = 0;
            B = 0;
            A = 255;
        }

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

        Color(const Color &color) {
            R = color.R;
            G = color.G;
            B = color.B;
            A = color.A;
        }

        SDL_Color ToSDLColor() {
            auto color = SDL_Color();
            color.r = R;
            color.g = G;
            color.b = B;
            color.a = A;
            return color;
        }

        Color &operator==(const Color &other) {
            if (&other != this) {
                R = other.R;
                G = other.G;
                B = other.B;
                A = other.A;
            }
            return *this;
        }

        bool operator==(const Color other) {
            return other.R == R && other.B == B && other.G == G && other.A == A;
        }
    };

    const Color Black(0, 0, 0);
    const Color White(1, 1, 1);
}// namespace nim
namespace YAML {
    template<>
    struct convert<nim::Color> {
        static YAML::Node encode(const nim::Color &color) {
            YAML::Node node;
            node.SetStyle(YAML::EmitterStyle::Flow);
            node.push_back(color.R);
            node.push_back(color.G);
            node.push_back(color.B);
            node.push_back(color.A);
            return node;
        }

        static bool decode(const YAML::Node &node, nim::Color &color) {
            if (!node.IsSequence() || node.size() != 4) return false;
            color.R = node[0].as<uint8_t>();
            color.G = node[1].as<uint8_t>();
            color.B = node[2].as<uint8_t>();
            color.A = node[3].as<uint8_t>();
            return true;
        }
    };
}// namespace YAML
#endif//COLOR_H