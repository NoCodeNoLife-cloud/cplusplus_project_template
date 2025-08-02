#pragma once
namespace common {
class IReadable abstract {
 public:
  virtual ~IReadable() = default;

  /// @brief Read one byte
  /// @return Byte value
  virtual auto read() -> int32_t = 0;
};
}  // namespace common
