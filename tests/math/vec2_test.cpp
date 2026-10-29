//
// Created by changemaker on 10/26/26.
//
#include <glex/mathem/vec2.h>
#include <gtest/gtest.h>

TEST(Vec2, DefaultIsZero) {
    constexpr mathem::Vec2 v{};
    EXPECT_EQ(v.x(), 0.0f);
    EXPECT_EQ(v.y(), 0.0f);
}

TEST(Vec2, ConstructorStoresComponents) {
    constexpr mathem::Vec2 v{3.0f, 4.0f};
    EXPECT_EQ(v.x(), 3.0f);
    EXPECT_EQ(v.y(), 4.0f);
}


TEST(Vec2, Dot) {
    constexpr mathem::Vec2 a{1.0f, 2.0f};
    constexpr mathem::Vec2 b{3.0f, 4.0f};
    EXPECT_EQ(mathem::dot(a, b), 11.0f);   // 1*3 + 2*4
}

TEST(Vec2, Length) {
    constexpr mathem::Vec2 v{3.0f, 4.0f};
    EXPECT_EQ(mathem::length(v), 5.0f);   // √(9 + 16)
}