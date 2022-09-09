#ifndef NMATH_H
#define NMATH_H

#include <algorithm>

namespace nim {
    inline float Normalize(const int &value, const int &min, const int &max) {
        return (static_cast<float>(value) - static_cast<float>(min)) / (max - min);
    }

    inline float Lerp(float a, float b, float t) {
        auto r = (1 - t) * a + t * b;
        return std::clamp(r, a, b);
    }
}// namespace nim

#endif//NMATH_H
