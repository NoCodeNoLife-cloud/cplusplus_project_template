#pragma once
#include <string>
#include <vector>

namespace common {
class StringUtil {
 public:
  static auto split(const std::string& target, char split_char) -> std::vector<std::string>;
  [[nodiscard]] static auto concatenate(const std::vector<std::string>& source, char split_char) -> std::string;
};
}  // namespace common
