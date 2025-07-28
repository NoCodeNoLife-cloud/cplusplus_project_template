#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <codecvt>

#include "AbstractReader.hpp"

namespace common {
class InputStreamReader final : public AbstractReader {
 public:
  explicit InputStreamReader(std::shared_ptr<AbstractReader> input);
  InputStreamReader(std::shared_ptr<AbstractReader> input,
                    const std::string& charsetName);
  ~InputStreamReader() override;
  auto read() -> int32_t override;
  auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;
  [[nodiscard]] auto ready() const -> bool override;
  auto close() -> void override;
  auto mark(size_t) -> void override;
  auto reset() -> void override;

 private:
  std::shared_ptr<AbstractReader> reader_;
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter_;
};
}  // namespace common
