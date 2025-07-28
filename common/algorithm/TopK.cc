#include "TopK.hpp"

namespace common {
TopK::TopK(const int k) : k(k) {}

auto TopK::add(const int num) -> void {
  if (minHeap.size() < k) {
    minHeap.push(num);
  } else if (num > minHeap.top()) {
    minHeap.pop();
    minHeap.push(num);
  }
}

auto TopK::getTopK() -> std::vector<int> {
  std::vector<int> result;
  while (!minHeap.empty()) {
    result.push_back(minHeap.top());
    minHeap.pop();
  }
  for (int num : result) {
    minHeap.push(num);
  }
  return result;
}
}  // namespace common
