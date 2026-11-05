//
// Created by changemaker on 11/5/26.
//


#include <glex/mathem/rect2.h>
#include <gtest/gtest.h>
#include <optional>

namespace gm = glex::mathem;

namespace {
    void expect_rect(gm::Rect2 r, float x0, float y0, float x1, float y1) {
        EXPECT_EQ(r.min().x(), x0);
        EXPECT_EQ(r.min().y(), y0);
        EXPECT_EQ(r.max().x(), x1);
        EXPECT_EQ(r.max().y(), y1);
    }
}

TEST(Rect2, DefaultIsZeroSizeAtOrigin) {
    expect_rect(gm::Rect2{}, 0.0f, 0.0f, 0.0f, 0.0f);
}

TEST(Rect2, FromOriginSize) {
    expect_rect(gm::from_origin_size(gm::Point2{10.0f, 20.0f}, gm::Vec2{30.0f, 40.0f}),
                10.0f, 20.0f, 40.0f, 60.0f);
}

TEST(Rect2, FromCornersAnyOrder) {
    expect_rect(gm::from_corners(gm::Point2{5.0f, 1.0f}, gm::Point2{2.0f, 4.0f}),
                2.0f, 1.0f, 5.0f, 4.0f);
}

TEST(Rect2, SizeAndCenter) {
    const gm::Rect2 r{gm::Point2{0.0f, 0.0f}, gm::Point2{10.0f, 4.0f}};
    const gm::Vec2 s = gm::size(r);
    EXPECT_EQ(s.x(), 10.0f);
    EXPECT_EQ(s.y(), 4.0f);
    const gm::Point2 c = gm::center(r);
    EXPECT_EQ(c.x(), 5.0f);
    EXPECT_EQ(c.y(), 2.0f);
}

TEST(Rect2, ContainsMinEdgeInMaxEdgeOut) {
    const gm::Rect2 r{gm::Point2{0.0f, 0.0f}, gm::Point2{10.0f, 10.0f}};
    EXPECT_TRUE(gm::contains(r, gm::Point2{0.0f, 0.0f}));     // min corner: in
    EXPECT_TRUE(gm::contains(r, gm::Point2{5.0f, 5.0f}));
    EXPECT_FALSE(gm::contains(r, gm::Point2{10.0f, 5.0f}));   // max edge: out
    EXPECT_FALSE(gm::contains(r, gm::Point2{5.0f, 10.0f}));
    EXPECT_FALSE(gm::contains(r, gm::Point2{-1.0f, 5.0f}));
}

TEST(Rect2, SharedEdgeBelongsToExactlyOne) {
    const gm::Rect2 left{gm::Point2{0.0f, 0.0f}, gm::Point2{10.0f, 10.0f}};
    const gm::Rect2 right{gm::Point2{10.0f, 0.0f}, gm::Point2{20.0f, 10.0f}};
    const gm::Point2 on_edge{10.0f, 5.0f};
    EXPECT_FALSE(gm::contains(left, on_edge));
    EXPECT_TRUE(gm::contains(right, on_edge));
}

TEST(Rect2, InsetShrinksAndGrows) {
    const gm::Rect2 r{gm::Point2{0.0f, 0.0f}, gm::Point2{10.0f, 10.0f}};
    expect_rect(gm::inset(r, gm::Vec2{2.0f, 3.0f}), 2.0f, 3.0f, 8.0f, 7.0f);
    expect_rect(gm::inset(r, gm::Vec2{-1.0f, -1.0f}), -1.0f, -1.0f, 11.0f, 11.0f);
}

TEST(Rect2, InsetTooMuchCollapsesToCenter) {
    // x: 10 wide, inset 8 per side, so it collapses to x = 5, the centre (G9). y is normal.
    const gm::Rect2 r{gm::Point2{0.0f, 0.0f}, gm::Point2{10.0f, 4.0f}};
    expect_rect(gm::inset(r, gm::Vec2{8.0f, 1.0f}), 5.0f, 1.0f, 5.0f, 3.0f);
}

TEST(Rect2, Intersection) {
    const std::optional<gm::Rect2> i = gm::intersection(
        gm::Rect2{gm::Point2{0.0f, 0.0f}, gm::Point2{10.0f, 10.0f}},
        gm::Rect2{gm::Point2{5.0f, 5.0f}, gm::Point2{15.0f, 15.0f}});
    ASSERT_TRUE(i.has_value());
    expect_rect(i.value_or(gm::Rect2{}), 5.0f, 5.0f, 10.0f, 10.0f);
}

TEST(Rect2, IntersectionNoneWhenTouchingOrApart) {
    const gm::Rect2 a{gm::Point2{0.0f, 0.0f}, gm::Point2{10.0f, 10.0f}};
    const gm::Rect2 touching{gm::Point2{10.0f, 0.0f}, gm::Point2{20.0f, 10.0f}};
    const gm::Rect2 apart{gm::Point2{20.0f, 20.0f}, gm::Point2{30.0f, 30.0f}};
    EXPECT_FALSE(gm::intersection(a, touching).has_value());
    EXPECT_FALSE(gm::intersection(a, apart).has_value());
}

TEST(Rect2, Merge) {
    expect_rect(gm::merge(gm::Rect2{gm::Point2{0.0f, 0.0f}, gm::Point2{2.0f, 2.0f}},
                          gm::Rect2{gm::Point2{5.0f, 1.0f}, gm::Point2{6.0f, 8.0f}}),
                0.0f, 0.0f, 6.0f, 8.0f);
}

#ifndef NDEBUG
TEST(Rect2, ReversedCornersAsserts) {
    EXPECT_DEATH(static_cast<void>(gm::Rect2(gm::Point2{5.0f, 0.0f}, gm::Point2{0.0f, 5.0f})), "");
}
#endif

TEST(Rect2, Translate) {
    const gm::Rect2 r{gm::Point2{0.0f, 0.0f}, gm::Point2{10.0f, 4.0f}};
    expect_rect(gm::translate(r, gm::Vec2{3.0f, -2.0f}), 3.0f, -2.0f, 13.0f, 2.0f);
}

TEST(Rect2, IsEmpty) {
    const gm::Rect2 flat{gm::Point2{0.0f, 0.0f}, gm::Point2{10.0f, 0.0f}};   // zero height
    EXPECT_TRUE(gm::is_empty(gm::Rect2{}));
    EXPECT_TRUE(gm::is_empty(flat));
    EXPECT_FALSE(gm::contains(flat, gm::Point2{0.0f, 0.0f}));   // empty contains nothing
    EXPECT_FALSE(gm::is_empty(gm::Rect2{gm::Point2{0.0f, 0.0f}, gm::Point2{10.0f, 4.0f}}));
}

TEST(Rect2, ApproxEq) {
    const gm::Rect2 r{gm::Point2{0.0f, 0.0f}, gm::Point2{1.0f, 1.0f}};
    EXPECT_TRUE(gm::approx_eq(r, gm::Rect2{gm::Point2{0.0f, 0.0f}, gm::Point2{1.0f, 1.0000005f}}));
    EXPECT_FALSE(gm::approx_eq(r, gm::Rect2{gm::Point2{0.0f, 0.0f}, gm::Point2{1.0f, 1.001f}}));
}