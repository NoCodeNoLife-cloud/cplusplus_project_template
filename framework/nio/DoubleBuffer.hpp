#pragma once
#include <vector>

#include "interface/IBuffer.hpp"

namespace framework::nio {
  class DoubleBuffer final : public interface::IBuffer {
  public:
    explicit DoubleBuffer(size_t capacity);

    auto put(double value) -> DoubleBuffer&;

    auto put(const std::vector<double>& values) -> DoubleBuffer&;

    auto get() -> double;

  private:
    std::vector<double> buffer_;
  };
} // namespace framework::nio
