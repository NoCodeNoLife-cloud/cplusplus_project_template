#include "StringUtil.hpp"

namespace common {
auto StringUtil::split(const std::string& target, const char split_char) -> std::vector<std::string> {
  std::vector<std::string> result;
  size_t start = 0;
  size_t pos = target.find(split_char);
  while (pos != std::string::npos) {
    result.push_back(target.substr(start, pos - start));
    start = pos + 1;
    pos = target.find(split_char, start);
  }
  result.push_back(target.substr(start));
  return result;
}

auto StringUtil::concatenate(const std::vector<std::string>& source, const char split_char) -> std::string {
  if (source.empty()) return "";
  std::string result = source[0];
  for (size_t i = 1; i < source.size(); ++i) {
    result += split_char;
    result += source[i];
  }
  return result;
}
}  // namespace common
