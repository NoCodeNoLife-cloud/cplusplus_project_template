#pragma once
#include <cstdint>

namespace common {
class Edge {
 public:
  /// @brief Construct an Edge with target vertex and weight
  /// @param to Target vertex
  /// @param weight Edge weight
  Edge(int32_t to, int32_t weight);

  /// @brief Get target vertex
  /// @return Target vertex
  [[nodiscard]] auto to() const -> int32_t;

  /// @brief Get edge weight
  /// @return Edge weight
  [[nodiscard]] auto weight() const -> int32_t;

  /// @brief Set target vertex
  /// @param to Target vertex
  auto setTo(int32_t to) -> void;

  /// @brief Set edge weight
  /// @param weight Edge weight
  auto setWeight(int32_t weight) -> void;

 private:
  int32_t to_{0};
  int32_t weight_{0};
};
}  // namespace common
