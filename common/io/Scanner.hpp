#pragma once
#include <string>
#include <sstream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

namespace common::io {
/// \brief A class for reading primitive types from a line-oriented input stream.
/// \details This class provides a way to read primitive types from a line-oriented input stream.
/// It is designed to be used with file streams, but can also be used with other types of input streams.
/// The class provides methods to read integers and doubles, as well as whole lines.
/// The methods will throw a std::runtime_error if there are no more tokens available.
class Scanner {
public:
  explicit Scanner(std::istream& input_stream) : input_(input_stream) {}
  /// \brief Reads an integer from the input stream.
  /// \details Reads an integer from the input stream.
  /// \return The integer read from the input stream.
  /// \throws std::runtime_error if there are no more tokens available.
  [[nodiscard]] auto nextInt() const -> int {
    if (std::string token; getNextToken(token)) {
      return std::stoi(token);
    }
    throw std::runtime_error("No more integers available.");
  }

  /// \brief Reads a double from the input stream.
  /// \details Reads a double from the input stream. It converts the next token into a double.
  /// \return The double read from the input stream.
  /// \throws std::runtime_error if there are no more tokens available.
  [[nodiscard]] auto nextDouble() const -> double {
    if (std::string token; getNextToken(token)) {
      return std::stod(token);
    }
    throw std::runtime_error("No more doubles available.");
  }

  /// \brief Reads a line from the input stream.
  /// \details Reads a line from the input stream.
  /// \return The line read from the input stream.
  [[nodiscard]] auto nextLine() const -> std::string {
    std::string line;
    std::getline(input_, line);
    return line;
  }

  /// \brief Retrieves the next token from the input stream.
  /// \details Retrieves the next token from the input stream.
  /// \param token The token to store the retrieved token in.
  /// \return true if a token was retrieved, false otherwise.
  auto getNextToken(std::string& token) const -> bool {
    if (std::string line; std::getline(input_, line)) {
      std::stringstream ss(line);
      ss >> token;
      return true;
    }
    return false;
  }

  /// \brief Retrieves the next tokens from the input stream.
  /// \details Retrieves the next tokens from the input stream.
  /// \param delimiter The delimiter to use for splitting the tokens. Defaults to space.
  /// \return The tokens retrieved from the input stream.
  [[nodiscard]] auto nextTokens(const char delimiter = ' ') const -> std::vector<std::string> {
    std::string line;
    std::getline(input_, line);
    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::is_any_of(std::string(1, delimiter)));
    return tokens;
  }

private:
  std::istream& input_;
};
}
