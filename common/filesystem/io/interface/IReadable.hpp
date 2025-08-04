#pragma once
namespace common {
/// @brief Interface for readable objects.
/// This interface defines the contract for objects that can be read from.
/// Implementing classes should provide functionality to read data, typically byte by byte.
class IReadable abstract {
 public:
  virtual ~IReadable() = default;

  /// @brief Read one byte
  /// @return Byte value
  virtual auto read() -> int32_t = 0;
};
}  // namespace common
