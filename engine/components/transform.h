#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "SDL.h"
#include "vector2d.h"
#include "yaml-cpp/yaml.h"

namespace nim {
    class Transform {
    public:
        Transform();
        Transform(Vector2 size, Vector2 position);
        Transform(const Transform &other);
        Transform(Transform &&other);
        ~Transform() = default;

        Transform &operator=(const Transform &other);
        Transform &operator=(Transform &&other);

        void Size(Vector2 *size);
        void Size(Vector2 &&size);
        void Position(const Vector2 *position);
        void Position(Vector2 &&position);
        void Size(float width, float height);
        void Position(float x, float y);

        SDL_FRect *GetRect();

    private:
        void SetRect();

    public:
        Vector2 size;
        Vector2 position;

    private:
        SDL_FRect rect;
    };
}// namespace nim

namespace YAML {
    template<>
    struct convert<nim::Transform *> {
        static YAML::Node encode(const nim::Transform *transform) {
            YAML::Node node;
            node["size"] = transform->size;
            node["position"] = transform->position;
            return node;
        }
    };
    template<>
    struct convert<nim::Transform> {
        static bool decode(const YAML::Node &node, nim::Transform &transform) {
            if (!node["size"] && !node["position"]) return false;
            auto size = node["size"].as<nim::Vector2>();
            auto position = node["position"].as<nim::Vector2>();
            transform.size = size;
            transform.position = position;
            return true;
        }
    };
}// namespace YAML
#endif// TRANSFORM_H