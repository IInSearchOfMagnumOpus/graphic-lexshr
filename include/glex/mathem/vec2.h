#pragma once
#include <cmath>
#include "glex/core/assert.h"
#include "glex//mathem/scalar.h"
#include <optional>

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

    [[nodiscard]] constexpr Vec2 lerp(Vec2 a, Vec2 b, float t) {
        return a + (b - a) * t;
    }

    [[nodiscard]] constexpr bool is_zero(Vec2 v) {
        return length_sq(v) < EPSILON * EPSILON;
    }

    // Length within EPSILON of 1. Near 1, squaring doubles a small gap (D-017).
    [[nodiscard]] inline bool is_normalized(Vec2 v) {
        return std::abs(length_sq(v) - 1.0f) < 2.0f * EPSILON;
    }

    [[nodiscard]] inline Vec2 normalize(Vec2 v) {
        GLEX_ASSERT(!is_zero(v));
        const float len = length(v);
        return v / len;
    }

    [[nodiscard]] constexpr bool approx_eq(Vec2 a, Vec2 b) {
        return is_zero(a - b);
    }

    // No direction when v is zero (D-017); the caller must check.
    [[nodiscard]] inline std::optional<Vec2> try_normalize(Vec2 v) {
        if (is_zero(v)) {
            return std::nullopt;
        }
        return normalize(v);
    }

    // Shadow of u on the line through onto. onto must not be zero (D-004).
    [[nodiscard]] constexpr Vec2 project_onto(Vec2 u, Vec2 onto) {
        GLEX_ASSERT(!is_zero(onto));
        return onto * (dot(u, onto) / length_sq(onto));
    }

    // Part of u at a right angle to onto: u minus its shadow. onto must not be zero.
    [[nodiscard]] constexpr Vec2 reject_from(Vec2 u, Vec2 onto) {
        return u - project_onto(u, onto);
    }

    [[nodiscard]] inline Vec2 reflect(Vec2 v, Vec2 n) {
        GLEX_ASSERT(is_normalized(n));
        return v - n * (2.0f * dot(v, n));
    }

    // Length-1 arrow at an angle in radians, anticlockwise from +x (y up).
    [[nodiscard]] inline Vec2 from_angle(float radians) {
        return Vec2{std::cos(radians), std::sin(radians)};
    }

    [[nodiscard]] inline Vec2 rotate(Vec2 v, float radians) {
        const Vec2 e = from_angle(radians);
        return e * v.x() + perp(e) * v.y();
    }

    // Angle of v in radians, anticlockwise from +x, between -π and π. v must not be zero.
    [[nodiscard]] inline float angle(Vec2 v) {
        GLEX_ASSERT(!is_zero(v));
        return std::atan2(v.y(), v.x());
    }

    // Per-part minimum: (smaller x, smaller y). Gives a box's low corner.
    [[nodiscard]] constexpr Vec2 min(Vec2 a, Vec2 b) {
        return Vec2{std::min(a.x(), b.x()), std::min(a.y(), b.y())};
    }

    // Per-part maximum: (larger x, larger y). Gives a box's high corner.
    [[nodiscard]] constexpr Vec2 max(Vec2 a, Vec2 b) {
        return Vec2{std::max(a.x(), b.x()), std::max(a.y(), b.y())};
    }

    // Per-part size: drops the signs.
    [[nodiscard]] inline Vec2 abs(Vec2 v) {
        return Vec2{std::abs(v.x()), std::abs(v.y())};
    }
} // namespace glex::mathem