#pragma once
#include <vector>

#include "interface/IBuffer.hpp"

namespace framework::nio {

class ShortBuffer final : public interface::IBuffer {
 public:
  explicit ShortBuffer(size_t capacity);

  static auto wrap(const short* data, size_t size) -> ShortBuffer;

  auto get() -> short;

  [[nodiscard]] auto get(size_t index) const -> short;

  auto put(short value) -> void;

  auto put(size_t index, short value) -> void;

  auto rewind() -> void override;

  auto data() -> short*;

  [[nodiscard]] auto data() const -> const short*;

 private:
  std::vector<short> buffer_{};
};

}  // namespace framework::nio
