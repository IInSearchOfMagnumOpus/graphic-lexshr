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