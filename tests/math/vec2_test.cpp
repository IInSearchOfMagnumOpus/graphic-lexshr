//
// Created by changemaker on 10/26/26.
//
#include <glex/mathem/vec2.h>
#include <gtest/gtest.h>

namespace gm = glex::mathem;

TEST(Vec2, DefaultIsZero) {
    constexpr gm::Vec2 v{};
    EXPECT_EQ(v.x(), 0.0f);
    EXPECT_EQ(v.y(), 0.0f);
}

TEST(Vec2, ConstructorStoresComponents) {
    constexpr gm::Vec2 v{3.0f, 4.0f};
    EXPECT_EQ(v.x(), 3.0f);
    EXPECT_EQ(v.y(), 4.0f);
}


TEST(Vec2, Dot) {
    constexpr gm::Vec2 a{1.0f, 2.0f};
    constexpr gm::Vec2 b{3.0f, 4.0f};
    EXPECT_EQ(gm::dot(a, b), 11.0f);   // 1*3 + 2*4
}

TEST(Vec2, Length) {
    constexpr gm::Vec2 v{3.0f, 4.0f};
    EXPECT_EQ(gm::length(v), 5.0f);   // √(9 + 16)
}

TEST(Vec2, LengthSq) {
    constexpr gm::Vec2 v{3.0f, 4.0f};
    EXPECT_EQ(gm::length_sq(v), 25.0f);   // 9 + 16
}

TEST(Vec2, Normalize) {
    constexpr gm::Vec2 v{3.0f, 4.0f};
    const auto n = gm::normalize(v);
    EXPECT_FLOAT_EQ(n.x(), 0.6f);
    EXPECT_FLOAT_EQ(n.y(), 0.8f);
}


TEST(Vec2, Add) {
    constexpr gm::Vec2 a{1.0f, 2.0f};
    constexpr gm::Vec2 b{3.0f, 4.0f};
    constexpr auto c = a + b;
    EXPECT_EQ(c.x(), 4.0f);
    EXPECT_EQ(c.y(), 6.0f);
}

TEST(Vec2, Subtract) {
    constexpr gm::Vec2 a{3.0f, 4.0f};
    constexpr gm::Vec2 b{1.0f, 2.0f};
    constexpr auto c = a - b;
    EXPECT_EQ(c.x(), 2.0f);
    EXPECT_EQ(c.y(), 2.0f);
}

TEST(Vec2, ScaleByNumber) {
    constexpr gm::Vec2 v{1.0f, 2.0f};
    constexpr auto s = v * 2.0f;
    EXPECT_EQ(s.x(), 2.0f);
    EXPECT_EQ(s.y(), 4.0f);
}

#ifndef NDEBUG
TEST(Vec2, NormalizeZeroAsserts) {
    constexpr gm::Vec2 v{};
    EXPECT_DEATH((void)gm::normalize(v), "Assertion failed");
}

TEST(Vec2, DivideByZeroAsserts) {
    constexpr gm::Vec2 v{1.0f, 1.0f};
    EXPECT_DEATH((void)(v / 0.0f), "operator/");
}

#endif
TEST(Vec2, Perp) {
    constexpr gm::Vec2 v{3.0f, 4.0f};
    constexpr auto p = gm::perp(v);
    EXPECT_EQ(p.x(), -4.0f);
    EXPECT_EQ(p.y(), 3.0f);
}

TEST(Vec2, PerpCw) {
    constexpr gm::Vec2 v{3.0f, 4.0f};
    constexpr auto p = gm::perp_cw(v);
    EXPECT_EQ(p.x(), 4.0f);
    EXPECT_EQ(p.y(), -3.0f);
}


TEST(Vec2, DistanceSq) {
    constexpr gm::Vec2 a{1.0f, 1.0f};
    constexpr gm::Vec2 b{4.0f, 5.0f};
    EXPECT_EQ(gm::distance_sq(a, b), 25.0f);   // arrow (3, 4)
}

TEST(Vec2, Distance) {
    constexpr gm::Vec2 a{1.0f, 1.0f};
    constexpr gm::Vec2 b{4.0f, 5.0f};
    EXPECT_EQ(gm::distance(a, b), 5.0f);
    EXPECT_EQ(gm::distance(b, a), 5.0f);       // same both ways
}

TEST(Vec2, Cross) {
    constexpr gm::Vec2 a{1.0f, 0.0f};
    EXPECT_EQ(gm::cross(a, gm::Vec2{1.0f, 1.0f}), 1.0f);    // anticlockwise
    EXPECT_EQ(gm::cross(a, gm::Vec2{1.0f, -1.0f}), -1.0f);  // clockwise
    EXPECT_EQ(gm::cross(a, gm::Vec2{2.0f, 0.0f}), 0.0f);    // same line
}

TEST(Vec2, ScaleNumberFirst) {
    constexpr gm::Vec2 v{1.0f, 2.0f};
    constexpr auto s = 2.0f * v;
    EXPECT_EQ(s.x(), 2.0f);
    EXPECT_EQ(s.y(), 4.0f);
}

TEST(Vec2, DivideByNumber) {
    constexpr gm::Vec2 v{2.0f, 4.0f};
    constexpr gm::Vec2 d = v / 2.0f;
    EXPECT_EQ(d.x(), 1.0f);
    EXPECT_EQ(d.y(), 2.0f);
}

TEST(Vec2, Negate) {
    constexpr glex::mathem::Vec2 v{3.0f, 4.0f};
    constexpr glex::mathem::Vec2 n = -v;
    EXPECT_EQ(n.x(), -3.0f);
    EXPECT_EQ(n.y(), -4.0f);
}

TEST(Vec2, Lerp) {
    constexpr gm::Vec2 a{0.0f, 0.0f};
    constexpr gm::Vec2 b{10.0f, 0.0f};
    constexpr gm::Vec2 mid = gm::lerp(a, b, 0.25f);
    constexpr gm::Vec2 end = gm::lerp(a, b, 1.0f);
    EXPECT_EQ(mid.x(), 2.5f);
    EXPECT_EQ(mid.y(), 0.0f);
    EXPECT_EQ(end.x(), 10.0f);
}

TEST(Vec2, IsZero) {
    EXPECT_TRUE(gm::is_zero(gm::Vec2{0.0f, 0.0f}));
    EXPECT_TRUE(gm::is_zero(gm::Vec2{5e-7f, 0.0f}));   // inside the circle
    EXPECT_FALSE(gm::is_zero(gm::Vec2{8e-7f, 8e-7f})); // in the box's corner, outside the circle
}


TEST(Vec2, IsNormalized) {
    EXPECT_TRUE(gm::is_normalized(gm::Vec2{1.0f, 0.0f}));
    EXPECT_TRUE(gm::is_normalized(gm::normalize(gm::Vec2{3.0f, 4.0f})));
    EXPECT_TRUE(gm::is_normalized(gm::Vec2{1.0000005f, 0.0f}));  // off by 5e-7: within EPSILON
    EXPECT_FALSE(gm::is_normalized(gm::Vec2{1.001f, 0.0f}));
    EXPECT_FALSE(gm::is_normalized(gm::Vec2{0.0f, 0.0f}));
}

TEST(Vec2, ApproxEq) {
    EXPECT_TRUE(gm::approx_eq(gm::Vec2{1.0f, 2.0f}, gm::Vec2{1.0f, 2.0f}));
    EXPECT_TRUE(gm::approx_eq(gm::Vec2{1.0f, 2.0f}, gm::Vec2{1.0f, 2.0000005f}));  // 5e-7 apart
    EXPECT_FALSE(gm::approx_eq(gm::Vec2{1.0f, 2.0f}, gm::Vec2{1.0f, 2.001f}));
    EXPECT_FALSE(gm::approx_eq(gm::Vec2{5e-4f, 0.0f}, gm::Vec2{0.0f, 0.0f}));      // D-017: not zero
}