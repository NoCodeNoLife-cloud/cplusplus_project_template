#include "src/graphics/Edge.hpp"

#include <cstdint>

namespace common
{
    Edge::Edge(const int32_t to, const int32_t weight) noexcept : to_(to), weight_(weight)
    {
    }

    auto Edge::to() const noexcept -> int32_t
    {
        return to_;
    }

    auto Edge::setTo(const int32_t to) noexcept -> void
    {
        to_ = to;
    }

    auto Edge::weight() const noexcept -> int32_t
    {
        return weight_;
    }

    auto Edge::setWeight(const int32_t weight) noexcept -> void
    {
        weight_ = weight;
    }
}
