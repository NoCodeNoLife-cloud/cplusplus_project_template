#include "Edge.hpp"

namespace common {
Edge::Edge(const int32_t to, const int32_t weight) : to_(to), weight_(weight) {}

auto Edge::to() const -> int32_t { return to_; }

auto Edge::weight() const -> int32_t { return weight_; }

auto Edge::setTo(const int32_t to) -> void { to_ = to; }

auto Edge::setWeight(const int32_t weight) -> void { weight_ = weight; }
}  // namespace common
