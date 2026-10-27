//
// Created by changemaker on 10/26/26.
//
#include <glex/math/vec2.h>
#include <gtest/gtest.h>

TEST(Vec2, DefaultIsZero) {
    constexpr glex::Vec2 v{};
    EXPECT_EQ(v.x(), 0.0f);
    EXPECT_EQ(v.y(), 0.0f);
}

TEST(Vec2, ConstructorStoresComponents) {
    constexpr glex::Vec2 v{3.0f, 4.0f};
    EXPECT_EQ(v.x(), 3.0f);
    EXPECT_EQ(v.y(), 4.0f);
}