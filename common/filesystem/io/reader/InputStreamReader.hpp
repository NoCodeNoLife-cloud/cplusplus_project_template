#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING  // NOLINT(*-reserved-identifier)
#include <codecvt>

#include "AbstractReader.hpp"

namespace common {
class InputStreamReader final : public AbstractReader {
 public:
  explicit InputStreamReader(std::shared_ptr<AbstractReader> input);
  InputStreamReader(std::shared_ptr<AbstractReader> input, const std::string& charsetName);
  ~InputStreamReader() override;

  /// @brief Read a single character.
  /// @return The character read, as an integer in the range 0 to 65535
  auto read() -> int32_t override;

  /// @brief Read characters into an array.
  /// @param cBuf Destination buffer
  /// @param off Offset at which to start storing characters
  /// @param len Maximum number of characters to read
  /// @return The number of characters read, or -1 if the end of the stream has been reached
  auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;

  /// @brief Reset the stream.
  [[nodiscard]] auto ready() const -> bool override;

  /// @brief Close the stream.
  auto close() -> void override;

  /// @brief Mark the current position in the stream.
  auto mark(size_t) -> void override;

  /// @brief Reset the stream to the most recent mark.
  auto reset() -> void override;

 private:
  std::shared_ptr<AbstractReader> reader_;
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter_;
};
}  // namespace common
