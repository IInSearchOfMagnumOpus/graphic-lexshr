
#pragma once
#include <optional>
#include "glex/core/assert.h"
#include "glex/mathem/point2.h"

namespace glex::mathem {
    // Axis-aligned box: every point from min up to (not including) max. Always min <= max.
    class Rect2 {
    public:
        constexpr Rect2() = default;   // zero-size box at the origin
        // Corners must already be in order (D-004).
        constexpr Rect2(Point2 lo, Point2 hi) : min_(lo), max_(hi) {
            GLEX_ASSERT(lo.x() <= hi.x() && lo.y() <= hi.y());
        }

        constexpr Point2 min() const { return min_; }
        constexpr Point2 max() const { return max_; }
    private:
        Point2 min_{};
        Point2 max_{};
    };

    // From a corner and a size, the way windows report themselves. Size must not be negative.
    [[nodiscard]] constexpr Rect2 from_origin_size(Point2 origin, Vec2 size) {
        return Rect2{origin, origin + size};
    }

    // From any two opposite corners, in any order.
    [[nodiscard]] constexpr Rect2 from_corners(Point2 a, Point2 b) {
        return Rect2{min(a, b), max(a, b)};
    }

    [[nodiscard]] constexpr Vec2 size(Rect2 r) {
        return r.max() - r.min();
    }

    [[nodiscard]] constexpr Point2 center(Rect2 r) {
        return r.min() + size(r) * 0.5f;
    }

    // Min edge in, max edge out, so rects sharing an edge never both contain a point on it.
    [[nodiscard]] constexpr bool contains(Rect2 r, Point2 p) {
        return p.x() >= r.min().x() && p.x() < r.max().x()
            && p.y() >= r.min().y() && p.y() < r.max().y();
    }

    // Shrinks each side by amount (negative grows). Too much collapses that axis to the centre.
    // min(.., c) <= c <= max(.., c), so the corners always stay in order.
    [[nodiscard]] constexpr Rect2 inset(Rect2 r, Vec2 amount) {
        const Point2 c = center(r);
        return Rect2{min(r.min() + amount, c), max(r.max() - amount, c)};
    }

    // The overlap of a and b. None if they only touch or don't meet: touching edges share no point.
    [[nodiscard]] constexpr std::optional<Rect2> intersection(Rect2 a, Rect2 b) {
        const Point2 lo = max(a.min(), b.min());
        const Point2 hi = min(a.max(), b.max());
        if (lo.x() >= hi.x() || lo.y() >= hi.y()) {
            return std::nullopt;
        }
        return Rect2{lo, hi};
    }

    // Smallest rect holding both. Called merge because union is a C++ keyword.
    [[nodiscard]] constexpr Rect2 merge(Rect2 a, Rect2 b) {
        return Rect2{min(a.min(), b.min()), max(a.max(), b.max())};
    }
} // namespace glex::mathem