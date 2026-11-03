#pragma once
#include <cmath>
#include "glex/core/assert.h"

namespace glex::mathem {
    class Vec2 {
    public:
        constexpr Vec2() = default;
        constexpr Vec2(float x, float y) : x_(x), y_(y) {}

        constexpr float x() const { return x_; }
        constexpr float y() const { return y_; }
    private:
        float x_{};
        float y_{};
    };

    [[nodiscard]] constexpr float dot(Vec2 a, Vec2 b) {
        return a.x() * b.x() + a.y() * b.y();
    }

    // Positive: b is anticlockwise from a (y up).
    [[nodiscard]] constexpr float cross(Vec2 a, Vec2 b) {
        return a.x() * b.y() - a.y() * b.x();
    }

    // Quarter turn anticlockwise (y up).
    [[nodiscard]] constexpr Vec2 perp(Vec2 v) {
        return Vec2{-v.y(), v.x()};
    }

    // Quarter turn clockwise (y up).
    [[nodiscard]] constexpr Vec2 perp_cw(Vec2 v) {
        return Vec2{v.y(), -v.x()};
    }

    [[nodiscard]] constexpr float length_sq(Vec2 v) {
        return dot(v, v);
    }

    [[nodiscard]] inline float length(Vec2 v) {
        return std::sqrt(length_sq(v));
    }

    [[nodiscard]] inline Vec2 normalize(Vec2 v) {
        const float len = length(v);
        GLEX_ASSERT(len > 0);
        return Vec2{v.x() / len, v.y() / len};
    }
    
    [[nodiscard]] constexpr Vec2 operator+(Vec2 a, Vec2 b) {
        return Vec2{a.x() + b.x(), a.y() + b.y()};
    }

    [[nodiscard]] constexpr Vec2 operator-(Vec2 a, Vec2 b) {
        return Vec2{a.x() - b.x(), a.y() - b.y()};
    }

    [[nodiscard]] constexpr Vec2 operator-(Vec2 v) {
        return Vec2{-v.x(), -v.y()};
    }
    
    [[nodiscard]] constexpr float distance_sq(Vec2 a, Vec2 b) {
        return length_sq(b - a);
    }

    [[nodiscard]] inline float distance(Vec2 a, Vec2 b) {
        return length(b - a);
    }

    [[nodiscard]] constexpr Vec2 operator*(Vec2 v, float s) {
        return Vec2{v.x() * s, v.y() * s};
    }

    [[nodiscard]] constexpr Vec2 operator*(float s, Vec2 v) {
        return v * s;
    }

    [[nodiscard]] constexpr Vec2 operator/(Vec2 v, float s) {
        GLEX_ASSERT(s != 0.0f);
        return Vec2{v.x() / s, v.y() / s};
    }

} // namespace glex::mathem