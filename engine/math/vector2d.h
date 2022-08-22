#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "yaml-cpp/yaml.h"

namespace nim {
    struct Vector2 {
        float x;
        float y;

        Vector2() {
            x = 0.f;
            y = 0.f;
        }

        Vector2(float a, float b) {
            x = a;
            y = b;
        }

        Vector2 &operator=(float value) {
            x = value;
            y = value;
            return *this;
        }

        Vector2 &operator=(Vector2 value) {
            x = value.x;
            y = value.y;
            return *this;
        }

        float w() const { return x; }
        float h() const { return y; }
        void w(float value) { x = value; }
        void h(float value) { y = value; }
    };

    struct Vector2int {
        int x;
        int y;

        Vector2int() {
            x = 0;
            y = 0;
        }

        Vector2int(int a, int b) {
            x = a;
            y = b;
        }

        Vector2int &operator=(int value) {
            x = value;
            y = value;
            return *this;
        }

        Vector2int &operator=(Vector2int value) {
            x = value.x;
            y = value.y;
            return *this;
        }

        int w() const { return x; }
        int h() const { return y; }
        void w(int value) { x = value; }
        void h(int value) { y = value; }
    };
}// namespace nim

namespace YAML {
    template<>
    struct convert<nim::Vector2> {
        static YAML::Node encode(const nim::Vector2 &vector) {
            YAML::Node node;
            node.SetStyle(YAML::EmitterStyle::Flow);
            node.push_back(vector.x);
            node.push_back(vector.y);
            return node;
        }

        static bool decode(const YAML::Node &node, nim::Vector2 &vector) {
            if (!node.IsSequence() || node.size() != 2) return false;
            vector.x = node[0].as<float>();
            vector.y = node[1].as<float>();
            return true;
        }
    };
    template<>
    struct convert<nim::Vector2int> {
        static YAML::Node encode(const nim::Vector2int &vector) {
            YAML::Node node;
            node.SetStyle(YAML::EmitterStyle::Flow);
            node.push_back(vector.x);
            node.push_back(vector.y);
            return node;
        }

        static bool decode(const YAML::Node &node, nim::Vector2int &vector) {
            if (!node.IsSequence() || node.size() != 2) return false;
            vector.x = node[0].as<int>();
            vector.y = node[1].as<int>();
            return true;
        }
    };
}// namespace YAML

#endif