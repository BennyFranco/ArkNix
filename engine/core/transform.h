#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vector2d.h"

namespace nim {
    class Transform {
    public:
        virtual inline float X() const { return position.x; }
        virtual inline float Y() const { return position.y; }
        virtual inline float Width() const { return size.x; }
        virtual inline float Height() const { return size.y; }
        virtual inline Vector2 Size() const { return size; }
        virtual inline Vector2 Position() const { return position; }

        virtual void X(float value) { position.x = value; }
        virtual void Y(float value) { position.y = value; }
        virtual void Width(float value) { size.x = value; }
        virtual void Height(float value) { size.y = value; }
        virtual void Size(Vector2 size) { this->size = size; }
        virtual void Position(Vector2 position) { this->position = position; }
        virtual void Size(float width, float height) {
            size.x = width;
            size.y = height;
        }
        virtual void Position(float x, float y) {
            position.x = x;
            position.y = y;
        }

    protected:
        Vector2 size;
        Vector2 position;
    };
}// namespace nim
#endif// TRANSFORM_H