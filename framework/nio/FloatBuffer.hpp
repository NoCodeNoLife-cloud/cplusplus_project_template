#pragma once
#include <vector>

#include "interface/IBuffer.hpp"

namespace framework::nio {

class FloatBuffer final : public interface::IBuffer {
 public:
  explicit FloatBuffer(size_t capacity);

  static auto allocate(size_t capacity) -> FloatBuffer;

  auto put(float value) -> void;

  auto put(const std::vector<float>& values) -> void;

  auto get() -> float;

  auto get(size_t length) -> std::vector<float>;

 private:
  std::vector<float> buffer_{};
};

}  // namespace framework::nio
