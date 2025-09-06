#pragma once
#include <boost/algorithm/string.hpp>
#include <string>

namespace fox {
/// @brief A utility class for scanning and parsing input streams.
/// The Scanner class provides methods for reading various data types from an input stream,
/// such as integers, doubles, strings, and lines. It also supports reading tokens separated
/// by delimiters. This class is designed to simplify input parsing operations.
class Scanner {
 public:
  explicit Scanner(std::istream& input_stream);

  /// @brief Reads the next integer from the input stream.
  /// This method parses the next token from the input stream and converts it to a 32-bit signed integer.
  /// It assumes that the next token in the stream represents a valid integer.
  /// @return The parsed integer value.
  [[nodiscard]] auto nextInt() const -> int32_t;

  /// @brief Reads the next double from the input stream.
  /// This method parses the next token from the input stream and converts it to a double precision floating point number.
  /// It assumes that the next token in the stream represents a valid double.
  /// @return The parsed double value.
  [[nodiscard]] auto nextDouble() const -> double;

  /// @brief Reads the next line from the input stream.
  /// This method reads characters from the input stream until it encounters a newline character or the end of the stream.
  /// @return The next line as a string, excluding the newline character.
  [[nodiscard]] auto nextLine() const -> std::string;

  /// @brief Reads the next token from the input stream.
  /// This method reads characters from the input stream until it encounters a whitespace character or the end of the stream.
  /// @param token A reference to a string where the next token will be stored.
  /// @return `true` if a token was successfully read, `false` if the end of the stream was reached.
  auto getNextToken(std::string& token) const -> bool;

  /// @brief Reads all tokens from the input stream until the end of the stream is reached.
  /// Tokens are separated by the specified delimiter character. By default, the delimiter is a space (' ').
  /// This method returns a vector containing all the tokens read from the stream.
  /// @param delimiter The character used to separate tokens in the input stream. Defaults to space (' ').
  /// @return A vector of strings, where each string is a token from the input stream.
  [[nodiscard]] auto nextTokens(char delimiter = ' ') const -> std::vector<std::string>;

 private:
  std::istream& input_;
};
}  // namespace fox
