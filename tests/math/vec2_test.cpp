//
// Created by changemaker on 10/26/26.
//
#include <glex/mathem/vec2.h>
#include <gtest/gtest.h>

TEST(Vec2, DefaultIsZero) {
    constexpr glex::mathem::Vec2 v{};
    EXPECT_EQ(v.x(), 0.0f);
    EXPECT_EQ(v.y(), 0.0f);
}

TEST(Vec2, ConstructorStoresComponents) {
    constexpr glex::mathem::Vec2 v{3.0f, 4.0f};
    EXPECT_EQ(v.x(), 3.0f);
    EXPECT_EQ(v.y(), 4.0f);
}


TEST(Vec2, Dot) {
    constexpr glex::mathem::Vec2 a{1.0f, 2.0f};
    constexpr glex::mathem::Vec2 b{3.0f, 4.0f};
    EXPECT_EQ(glex::mathem::dot(a, b), 11.0f);   // 1*3 + 2*4
}

TEST(Vec2, Length) {
    constexpr glex::mathem::Vec2 v{3.0f, 4.0f};
    EXPECT_EQ(glex::mathem::length(v), 5.0f);   // √(9 + 16)
}

TEST(Vec2, LengthSq) {
    constexpr glex::mathem::Vec2 v{3.0f, 4.0f};
    EXPECT_EQ(glex::mathem::length_sq(v), 25.0f);   // 9 + 16
}

TEST(Vec2, Normalize) {
    constexpr glex::mathem::Vec2 v{3.0f, 4.0f};
    const auto n = glex::mathem::normalize(v);
    EXPECT_FLOAT_EQ(n.x(), 0.6f);
    EXPECT_FLOAT_EQ(n.y(), 0.8f);
}


TEST(Vec2, Add) {
    constexpr glex::mathem::Vec2 a{1.0f, 2.0f};
    constexpr glex::mathem::Vec2 b{3.0f, 4.0f};
    constexpr auto c = a + b;
    EXPECT_EQ(c.x(), 4.0f);
    EXPECT_EQ(c.y(), 6.0f);
}

TEST(Vec2, Subtract) {
    constexpr glex::mathem::Vec2 a{3.0f, 4.0f};
    constexpr glex::mathem::Vec2 b{1.0f, 2.0f};
    constexpr auto c = a - b;
    EXPECT_EQ(c.x(), 2.0f);
    EXPECT_EQ(c.y(), 2.0f);
}

TEST(Vec2, ScaleByNumber) {
    constexpr glex::mathem::Vec2 v{1.0f, 2.0f};
    constexpr auto s = v * 2.0f;
    EXPECT_EQ(s.x(), 2.0f);
    EXPECT_EQ(s.y(), 4.0f);
}

#ifndef NDEBUG
TEST(Vec2, NormalizeZeroAsserts) {
    constexpr glex::mathem::Vec2 v{};
    EXPECT_DEATH((void)glex::mathem::normalize(v), "Assertion failed");
}

TEST(Vec2, DivideByZeroAsserts) {
    constexpr glex::mathem::Vec2 v{1.0f, 1.0f};
    EXPECT_DEATH((void)(v / 0.0f), "operator/");
}

#endif
TEST(Vec2, Perp) {
    constexpr glex::mathem::Vec2 v{3.0f, 4.0f};
    constexpr auto p = glex::mathem::perp(v);
    EXPECT_EQ(p.x(), -4.0f);
    EXPECT_EQ(p.y(), 3.0f);
}

TEST(Vec2, PerpCw) {
    constexpr glex::mathem::Vec2 v{3.0f, 4.0f};
    constexpr auto p = glex::mathem::perp_cw(v);
    EXPECT_EQ(p.x(), 4.0f);
    EXPECT_EQ(p.y(), -3.0f);
}


TEST(Vec2, DistanceSq) {
    constexpr glex::mathem::Vec2 a{1.0f, 1.0f};
    constexpr glex::mathem::Vec2 b{4.0f, 5.0f};
    EXPECT_EQ(glex::mathem::distance_sq(a, b), 25.0f);   // arrow (3, 4)
}

TEST(Vec2, Distance) {
    constexpr glex::mathem::Vec2 a{1.0f, 1.0f};
    constexpr glex::mathem::Vec2 b{4.0f, 5.0f};
    EXPECT_EQ(glex::mathem::distance(a, b), 5.0f);
    EXPECT_EQ(glex::mathem::distance(b, a), 5.0f);       // same both ways
}

TEST(Vec2, Cross) {
    constexpr glex::mathem::Vec2 a{1.0f, 0.0f};
    EXPECT_EQ(glex::mathem::cross(a, glex::mathem::Vec2{1.0f, 1.0f}), 1.0f);    // anticlockwise
    EXPECT_EQ(glex::mathem::cross(a, glex::mathem::Vec2{1.0f, -1.0f}), -1.0f);  // clockwise
    EXPECT_EQ(glex::mathem::cross(a, glex::mathem::Vec2{2.0f, 0.0f}), 0.0f);    // same line
}

TEST(Vec2, ScaleNumberFirst) {
    constexpr glex::mathem::Vec2 v{1.0f, 2.0f};
    constexpr auto s = 2.0f * v;
    EXPECT_EQ(s.x(), 2.0f);
    EXPECT_EQ(s.y(), 4.0f);
}

TEST(Vec2, DivideByNumber) {
    constexpr glex::mathem::Vec2 v{2.0f, 4.0f};
    constexpr auto d = v / 2.0f;
    EXPECT_EQ(d.x(), 1.0f);
    EXPECT_EQ(d.y(), 2.0f);
}