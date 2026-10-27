#pragma once

namespace glex {

    class Vec2 {
    public:
        constexpr Vec2() = default;
        constexpr Vec2(float x, float y) : x_(x), y_(y) {}

        constexpr float x() const { return x_; }
        constexpr float y() const { return y_; }
        void set_x(float v) { x_ = v; }
        void set_y(float v) { y_ = v; }

    private:
        float x_{};
        float y_{};
    };

} // namespace glex