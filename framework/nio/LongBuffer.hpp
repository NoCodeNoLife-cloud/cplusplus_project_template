#pragma once
#include <vector>
#include <nio/interface/IBuffer.hpp>

namespace framework::nio {
  class LongBuffer final : public interface::IBuffer {
  public:
    explicit LongBuffer(std::size_t capacity);
    auto get() -> int64_t;
    auto put(int64_t value) -> void;

  private:
    std::vector<int64_t> buffer_{};
  };
}
