#include "Scanner.hpp"

#include <boost/tokenizer.hpp>
#include <sstream>

namespace common {
Scanner::Scanner(std::istream& input_stream) : input_(input_stream) {}

auto Scanner::nextInt() const -> int32_t {
  if (std::string token; getNextToken(token)) {
    return std::stoi(token);
  }
  throw std::runtime_error("No more integers available.");
}

auto Scanner::nextDouble() const -> double {
  if (std::string token; getNextToken(token)) {
    return std::stod(token);
  }
  throw std::runtime_error("No more doubles available.");
}

auto Scanner::nextLine() const -> std::string {
  std::string line;
  std::getline(input_, line);
  return line;
}

auto Scanner::getNextToken(std::string& token) const -> bool {
  if (std::string line; std::getline(input_, line)) {
    std::stringstream ss(line);
    ss >> token;
    return true;
  }
  return false;
}

auto Scanner::nextTokens(const char delimiter) const -> std::vector<std::string> {
  std::string line;
  std::getline(input_, line);
  std::vector<std::string> tokens;
  split(tokens, line, boost::is_any_of(std::string(1, delimiter)));
  return tokens;
}
}  // namespace common
