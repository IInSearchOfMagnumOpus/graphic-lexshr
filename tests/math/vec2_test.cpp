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

TEST(Vec2, ProjectOntoZeroAsserts) {
    constexpr gm::Vec2 u{3.0f, 4.0f};
    EXPECT_DEATH((void)gm::project_onto(u, gm::Vec2{0.0f, 0.0f}), "project_onto");
}

TEST(Vec2, ReflectNonUnitNormalAsserts) {
    const gm::Vec2 v{3.0f, -4.0f};
    EXPECT_DEATH((void)gm::reflect(v, gm::Vec2{0.0f, 2.0f}), "reflect");
}

TEST(Vec2, AngleOfZeroAsserts) {
    EXPECT_DEATH((void)gm::angle(gm::Vec2{0.0f, 0.0f}), "angle");
}

TEST(Vec2, SignedAngleToZeroAsserts) {
    const gm::Vec2 v{1.0f, 0.0f};
    EXPECT_DEATH((void)gm::signed_angle_to(v, gm::Vec2{0.0f, 0.0f}), "signed_angle_to");
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

TEST(Vec2, TryNormalize) {
    const std::optional<gm::Vec2> n = gm::try_normalize(gm::Vec2{3.0f, 4.0f});
    if (!n.has_value()) {
        FAIL() << "expected a direction for (3, 4)";
    }
    EXPECT_FLOAT_EQ(n->x(), 0.6f);
    EXPECT_FLOAT_EQ(n->y(), 0.8f);
    EXPECT_FALSE(gm::try_normalize(gm::Vec2{0.0f, 0.0f}).has_value());
    EXPECT_FALSE(gm::try_normalize(gm::Vec2{5e-7f, 0.0f}).has_value());  // too short for a direction
}

TEST(Vec2, ProjectOnto) {
    constexpr gm::Vec2 u{3.0f, 4.0f};
    constexpr gm::Vec2 p = gm::project_onto(u, gm::Vec2{2.0f, 0.0f});  // onto's length doesn't matter
    EXPECT_EQ(p.x(), 3.0f);
    EXPECT_EQ(p.y(), 0.0f);
}

TEST(Vec2, RejectFrom) {
    constexpr gm::Vec2 u{4.0f, 2.0f};
    constexpr gm::Vec2 onto{1.0f, 1.0f};
    constexpr gm::Vec2 r = gm::reject_from(u, onto);
    EXPECT_EQ(r.x(), 1.0f);
    EXPECT_EQ(r.y(), -1.0f);
    EXPECT_EQ(gm::dot(r, onto), 0.0f);                              // right angle to onto
    EXPECT_TRUE(gm::approx_eq(gm::project_onto(u, onto) + r, u));   // the two parts rebuild u
}

TEST(Vec2, Reflect) {
    const gm::Vec2 v{3.0f, -4.0f};
    const gm::Vec2 r = gm::reflect(v, gm::Vec2{0.0f, 1.0f});
    EXPECT_EQ(r.x(), 3.0f);
    EXPECT_EQ(r.y(), 4.0f);
    EXPECT_FLOAT_EQ(gm::length(r), gm::length(v));   // a bounce keeps the speed
}

TEST(Vec2, FromAngle) {
    constexpr float pi = std::numbers::pi_v<float>;
    EXPECT_TRUE(gm::approx_eq(gm::from_angle(0.0f), gm::Vec2{1.0f, 0.0f}));
    EXPECT_TRUE(gm::approx_eq(gm::from_angle(pi / 2.0f), gm::Vec2{0.0f, 1.0f}));
    EXPECT_TRUE(gm::approx_eq(gm::from_angle(pi), gm::Vec2{-1.0f, 0.0f}));
    EXPECT_TRUE(gm::is_normalized(gm::from_angle(1.0f)));   // always length 1
}

TEST(Vec2, Rotate) {
    constexpr float pi = std::numbers::pi_v<float>;
    const gm::Vec2 v{3.0f, 4.0f};
    EXPECT_TRUE(gm::approx_eq(gm::rotate(gm::Vec2{1.0f, 0.0f}, pi / 2.0f), gm::Vec2{0.0f, 1.0f}));
    EXPECT_TRUE(gm::approx_eq(gm::rotate(v, pi / 2.0f), gm::perp(v)));   // quarter turn = perp
    EXPECT_TRUE(gm::approx_eq(gm::rotate(v, pi), -v));                    // half turn = flip
    EXPECT_FLOAT_EQ(gm::length(gm::rotate(v, 1.0f)), gm::length(v));      // turning keeps the length
}

TEST(Vec2, Angle) {
    constexpr float pi = std::numbers::pi_v<float>;
    EXPECT_FLOAT_EQ(gm::angle(gm::Vec2{1.0f, 0.0f}), 0.0f);
    EXPECT_FLOAT_EQ(gm::angle(gm::Vec2{0.0f, 2.0f}), pi / 2.0f);
    EXPECT_FLOAT_EQ(gm::angle(gm::Vec2{1.0f, 1.0f}), pi / 4.0f);
    EXPECT_FLOAT_EQ(gm::angle(gm::Vec2{-1.0f, -1.0f}), -3.0f * pi / 4.0f);  // atan(y/x) would say π/4
}
TEST(Vec2, MinMax) {
    const gm::Vec2 a{1.0f, 5.0f};
    const gm::Vec2 b{4.0f, 3.0f};
    const gm::Vec2 lo = gm::min(a, b);
    const gm::Vec2 hi = gm::max(a, b);
    EXPECT_EQ(lo.x(), 1.0f);
    EXPECT_EQ(lo.y(), 3.0f);   // the two parts come from different arrows
    EXPECT_EQ(hi.x(), 4.0f);
    EXPECT_EQ(hi.y(), 5.0f);
}

TEST(Vec2, Abs) {
    const gm::Vec2 v = gm::abs(gm::Vec2{-3.0f, 4.0f});
    EXPECT_EQ(v.x(), 3.0f);
    EXPECT_EQ(v.y(), 4.0f);
}
TEST(Vec2, SignedAngleTo) {
    constexpr float pi = std::numbers::pi_v<float>;
    const gm::Vec2 x_axis{1.0f, 0.0f};
    const gm::Vec2 y_axis{0.0f, 1.0f};
    EXPECT_FLOAT_EQ(gm::signed_angle_to(x_axis, y_axis), pi / 2.0f);    // anticlockwise: positive
    EXPECT_FLOAT_EQ(gm::signed_angle_to(y_axis, x_axis), -pi / 2.0f);   // clockwise: negative
}

TEST(Vec2, AngleBetween) {
    constexpr float pi = std::numbers::pi_v<float>;
    EXPECT_FLOAT_EQ(gm::angle_between(gm::Vec2{0.0f, 1.0f}, gm::Vec2{1.0f, 0.0f}), pi / 2.0f);
    const gm::Vec2 v{0.1f, 0.3f};
    EXPECT_EQ(gm::angle_between(v, v), 0.0f);   // same arrow: 0, never NaN (G9)
}

TEST(Vec2, Constants) {
    EXPECT_EQ(gm::Vec2::ZERO.x(), 0.0f);
    EXPECT_EQ(gm::Vec2::ZERO.y(), 0.0f);
    EXPECT_EQ(gm::Vec2::ONE.x(), 1.0f);
    EXPECT_EQ(gm::Vec2::ONE.y(), 1.0f);
}