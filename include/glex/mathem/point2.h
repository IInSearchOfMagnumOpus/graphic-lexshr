#pragma once
#include <algorithm>
#include "glex/mathem/vec2.h"

namespace glex::mathem {
    // A place, not a move. Same two floats as Vec2, but its own type, so:
    //   point - point  = vector   (the move from one to the other)
    //   point + vector = point
    //   point - vector = point
    //   point + point  : not defined, so it won't compile
    // The vector from the origin is p - Point2::ORIGIN; back is Point2::ORIGIN + v.
    class Point2 {
    private:
        float x_{};
        float y_{};
    public:
        static const Point2 ORIGIN;
        constexpr Point2() = default;   // same as ORIGIN: x_{} and y_{} start at 0
        constexpr Point2(float x, float y) : x_(x), y_(y) {}

        constexpr float x() const { return x_; }
        constexpr float y() const { return y_; }
    };

    inline constexpr Point2 Point2::ORIGIN{0.0f, 0.0f};

    // The move from b to a.
    [[nodiscard]] constexpr Vec2 operator-(Point2 a, Point2 b) {
        return Vec2{a.x() - b.x(), a.y() - b.y()};
    }

    [[nodiscard]] constexpr Point2 operator+(Point2 p, Vec2 v) {
        return Point2{p.x() + v.x(), p.y() + v.y()};
    }

    [[nodiscard]] constexpr Point2 operator-(Point2 p, Vec2 v) {
        return Point2{p.x() - v.x(), p.y() - v.y()};
    }

    [[nodiscard]] constexpr float distance_sq(Point2 a, Point2 b) {
        return length_sq(b - a);
    }

    [[nodiscard]] inline float distance(Point2 a, Point2 b) {
        return length(b - a);
    }

    // Uses only point - point and point + vector, so no step gets around the type.
    [[nodiscard]] constexpr Point2 lerp(Point2 a, Point2 b, float t) {
        return a + (b - a) * t;
    }

    // Same place within EPSILON: the move between them is zero (D-017).
    [[nodiscard]] constexpr bool approx_eq(Point2 a, Point2 b) {
        return is_zero(a - b);
    }

    // Per-part minimum: (smaller x, smaller y). Gives a box's low corner.
    [[nodiscard]] constexpr Point2 min(Point2 a, Point2 b) {
        return Point2{std::min(a.x(), b.x()), std::min(a.y(), b.y())};
    }

    // Per-part maximum: (larger x, larger y). Gives a box's high corner.
    [[nodiscard]] constexpr Point2 max(Point2 a, Point2 b) {
        return Point2{std::max(a.x(), b.x()), std::max(a.y(), b.y())};
    }
} // namespace glex::mathem
