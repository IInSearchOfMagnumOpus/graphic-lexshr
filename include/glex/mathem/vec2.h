#pragma once

namespace mathem {
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
} // namespace glex::mathem