#include "TopK.hpp"

namespace common::data_structure {
    TopK::TopK(const int32_t k)
        : k_(k) {
        if (k <= 0) {
            throw std::invalid_argument("k must be positive");
        }
    }

    auto TopK::add(const int32_t num) -> void {
        if (minHeap_.size() < k_) {
            minHeap_.push(num);
        } else if (num > minHeap_.top()) {
            minHeap_.pop();
            minHeap_.push(num);
        }
    }

    auto TopK::getTopK() -> std::vector<int32_t> {
        std::vector<int32_t> result;
        while (!minHeap_.empty()) {
            result.push_back(minHeap_.top());
            minHeap_.pop();
        }
        for (int32_t num: result) {
            minHeap_.push(num);
        }
        return result;
    }

    auto TopK::size() const -> size_t {
        return minHeap_.size();
    }

    auto TopK::empty() const -> bool {
        return minHeap_.empty();
    }
}
