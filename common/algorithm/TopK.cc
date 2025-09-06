#include "TopK.hpp"

namespace fox {
TopK::TopK(const int32_t k) : k(k) {}

auto TopK::add(const int32_t num) -> void {
  if (minHeap.size() < k) {
    minHeap.push(num);
  } else if (num > minHeap.top()) {
    minHeap.pop();
    minHeap.push(num);
  }
}

auto TopK::getTopK() -> std::vector<int32_t> {
  std::vector<int32_t> result;
  while (!minHeap.empty()) {
    result.push_back(minHeap.top());
    minHeap.pop();
  }
  for (int32_t num : result) {
    minHeap.push(num);
  }
  return result;
}
}  // namespace fox
