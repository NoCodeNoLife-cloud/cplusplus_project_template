#pragma once
#include <string>

namespace common {
class SimpleDateFormatter {
 public:
  explicit SimpleDateFormatter(const std::string& pattern);
  auto applyPattern(const std::string& newPattern) -> void;
  [[nodiscard]] auto toPattern() const -> std::string;
  [[nodiscard]] auto format(const std::tm& date) const -> std::string;
  [[nodiscard]] auto parse(const std::string& dateStr) const -> std::tm;
  [[nodiscard]] auto equals(const SimpleDateFormatter& other) const -> bool;
  [[nodiscard]] auto hashCode() const -> size_t;

 private:
  std::string pattern_;
  static auto validatePattern(const std::string& pat) -> void;
};
}  // namespace common
