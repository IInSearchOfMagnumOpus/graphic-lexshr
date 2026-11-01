#include <glex/mathem/scalar.h>
#include <gtest/gtest.h>

using namespace glex::mathem;

TEST(Scalar, ApproxEq) {
    EXPECT_TRUE(approx_eq(1.0f, 1.0f + EPSILON * 0.5f));
    EXPECT_FALSE(approx_eq(1.0f, 1.0f + EPSILON * 2.0f));
}

TEST(Scalar, ApproxZero) {
    EXPECT_TRUE(approx_zero(EPSILON * 0.5f));
    EXPECT_FALSE(approx_zero(EPSILON * 2.0f));
}
