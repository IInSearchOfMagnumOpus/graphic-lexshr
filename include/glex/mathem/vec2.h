#pragma once
#include <cmath>

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

    [[nodiscard]] inline float length(Vec2 v) {
        return std::sqrt(dot(v, v));
    }

    [[nodiscard]] inline Vec2 normalize(Vec2 v) {
        const float len = length(v);
        return Vec2{v.x() / len, v.y() / len};
    }
    
    [[nodiscard]] constexpr Vec2 operator+(Vec2 a, Vec2 b) {
        return Vec2{a.x() + b.x(), a.y() + b.y()};
    }

    [[nodiscard]] constexpr Vec2 operator-(Vec2 a, Vec2 b) {
        return Vec2{a.x() - b.x(), a.y() - b.y()};
    }

    [[nodiscard]] constexpr Vec2 operator*(Vec2 v, float s) {
        return Vec2{v.x() * s, v.y() * s};
    }

} // namespace glex::mathem