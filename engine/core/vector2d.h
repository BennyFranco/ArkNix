#ifndef VECTOR2D_H
#define VECTOR2D_H

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

    float w() const { return x; }
    float h() const { return y; }
    void w(float value) { x = value; }
    void h(float value) { y = value; }
};

#endif