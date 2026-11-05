//
// Created by changemaker on 11/5/26.
//

#include <glex/mathem/point2.h>
#include <gtest/gtest.h>

namespace gm = glex::mathem;

TEST(Point2, DefaultIsOrigin) {
    const gm::Point2 p{};
    EXPECT_EQ(p.x(), 0.0f);
    EXPECT_EQ(p.y(), 0.0f);
    EXPECT_EQ(gm::Point2::ORIGIN.x(), 0.0f);
    EXPECT_EQ(gm::Point2::ORIGIN.y(), 0.0f);
}

TEST(Point2, PointMinusPointIsVector) {
    const gm::Vec2 d = gm::Point2{5.0f, 3.0f} - gm::Point2{2.0f, 1.0f};
    EXPECT_EQ(d.x(), 3.0f);
    EXPECT_EQ(d.y(), 2.0f);
}

TEST(Point2, PlusAndMinusVector) {
    const gm::Point2 p{1.0f, 2.0f};
    const gm::Vec2 v{3.0f, 4.0f};
    const gm::Point2 moved = p + v;
    EXPECT_EQ(moved.x(), 4.0f);
    EXPECT_EQ(moved.y(), 6.0f);
    const gm::Point2 back = moved - v;
    EXPECT_EQ(back.x(), 1.0f);
    EXPECT_EQ(back.y(), 2.0f);
}

TEST(Point2, Distance) {
    const gm::Point2 a{0.0f, 0.0f};
    const gm::Point2 b{3.0f, 4.0f};
    EXPECT_EQ(gm::distance_sq(a, b), 25.0f);
    EXPECT_EQ(gm::distance(a, b), 5.0f);   // sqrt(25) is exactly 5 in floats
}

TEST(Point2, Lerp) {
    const gm::Point2 mid = gm::lerp(gm::Point2{0.0f, 0.0f}, gm::Point2{10.0f, 4.0f}, 0.5f);
    EXPECT_EQ(mid.x(), 5.0f);
    EXPECT_EQ(mid.y(), 2.0f);
}

TEST(Point2, ApproxEq) {
    const gm::Point2 p{1.0f, 2.0f};
    EXPECT_TRUE(gm::approx_eq(p, gm::Point2{1.0f, 2.0000005f}));   // gap under EPSILON
    EXPECT_FALSE(gm::approx_eq(p, gm::Point2{1.0f, 2.001f}));
}

TEST(Point2, MinMax) {
    const gm::Point2 lo = gm::min(gm::Point2{1.0f, 5.0f}, gm::Point2{3.0f, 2.0f});
    const gm::Point2 hi = gm::max(gm::Point2{1.0f, 5.0f}, gm::Point2{3.0f, 2.0f});
    EXPECT_EQ(lo.x(), 1.0f);
    EXPECT_EQ(lo.y(), 2.0f);
    EXPECT_EQ(hi.x(), 3.0f);
    EXPECT_EQ(hi.y(), 5.0f);
}