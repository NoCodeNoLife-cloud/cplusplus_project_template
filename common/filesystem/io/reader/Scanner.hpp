#pragma once
#include <boost/algorithm/string.hpp>
#include <string>

namespace common {
class Scanner {
 public:
  explicit Scanner(std::istream& input_stream);
  [[nodiscard]] auto nextInt() const -> int32_t;
  [[nodiscard]] auto nextDouble() const -> double;
  [[nodiscard]] auto nextLine() const -> std::string;
  auto getNextToken(std::string& token) const -> bool;
  [[nodiscard]] auto nextTokens(char delimiter = ' ') const -> std::vector<std::string>;

 private:
  std::istream& input_;
};
}  // namespace common
