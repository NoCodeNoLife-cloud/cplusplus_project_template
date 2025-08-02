#pragma once
#include <queue>
#include <vector>

namespace common {
class TopK final {
 public:
  explicit TopK(int k);

  /// @brief Add a number to the TopK.
  /// @param num The number to add.
  auto add(int num) -> void;

  /// @brief Get the top k numbers.
  /// @return The top k numbers.
  auto getTopK() -> std::vector<int>;

 private:
  int k;
  std::priority_queue<int, std::vector<int>, std::greater<>> minHeap;
};
}  // namespace common
