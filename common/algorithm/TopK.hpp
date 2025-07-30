#pragma once
#include <queue>
#include <vector>

namespace common {
class TopK final {
 public:
  explicit TopK(int k);

  auto add(int num) -> void;

  auto getTopK() -> std::vector<int>;

 private:
  int k;
  std::priority_queue<int, std::vector<int>, std::greater<>> minHeap;
};
}  // namespace common
