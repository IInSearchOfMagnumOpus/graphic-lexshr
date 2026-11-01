//
// Created by changemaker on 11/1/26.
//
#pragma once
#include <cmath>

namespace glex::mathem {
    // G3: one absolute tolerance, shared by every math type.
    inline constexpr float EPSILON = 1e-6f;

    [[nodiscard]] inline bool approx_eq(float a, float b) {
        return std::abs(a - b) < EPSILON;
    }

    [[nodiscard]] inline bool approx_zero(float x) {
        return approx_eq(x, 0.0f);
    }
} // namespace glex::mathem
