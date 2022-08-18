#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vector2d.h"

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

    public:
        Vector2 size;
        Vector2 position;
    };
}// namespace nim
#endif// TRANSFORM_H