#pragma once
#include <boost/algorithm/string.hpp>
#include <istream>
#include <stdexcept>
#include <string>
#include <vector>

namespace fox
{
    /// @brief A utility class for scanning and parsing input streams.
    /// The Scanner class provides methods for reading various data types from an input stream,
    /// such as integers, doubles, strings, and lines. It also supports reading tokens separated
    /// by delimiters. This class is designed to simplify input parsing operations.
    class Scanner
    {
    public:
        explicit Scanner(std::istream& input_stream);

        /// @brief Reads the next integer from the input stream.
        /// This method parses the next token from the input stream and converts it to a 32-bit signed integer.
        /// It assumes that the next token in the stream represents a valid integer.
        /// @return The parsed integer value.
        /// @throws std::runtime_error if no more integers are available or parsing fails.
        /// @throws std::invalid_argument if the token cannot be converted to an integer.
        /// @throws std::out_of_range if the token represents a number out of the range of int32_t.
        [[nodiscard]] auto nextInt() const -> int32_t;

        /// @brief Reads the next double from the input stream.
        /// This method parses the next token from the input stream and converts it to a double precision floating point
        /// number. It assumes that the next token in the stream represents a valid double.
        /// @return The parsed double value.
        /// @throws std::runtime_error if no more doubles are available or parsing fails.
        /// @throws std::invalid_argument if the token cannot be converted to a double.
        /// @throws std::out_of_range if the token represents a number out of the range of double.
        [[nodiscard]] auto nextDouble() const -> double;

        /// @brief Reads the next line from the input stream.
        /// This method reads characters from the input stream until it encounters a newline character or the end of the
        /// stream.
        /// @return The next line as a string, excluding the newline character.
        [[nodiscard]] auto nextLine() const -> std::string;

        /// @brief Reads the next token from the input stream.
        /// This method reads characters from the input stream until it encounters a whitespace character or the end of the
        /// stream.
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

    inline Scanner::Scanner(std::istream& input_stream) : input_(input_stream)
    {
    }

    inline auto Scanner::nextInt() const -> int32_t
    {
        if (std::string token; getNextToken(token))
        {
            try
            {
                return std::stoi(token);
            }
            catch (const std::exception&)
            {
                throw std::runtime_error("Failed to parse integer: " + token);
            }
        }
        throw std::runtime_error("No more integers available.");
    }

    inline auto Scanner::nextDouble() const -> double
    {
        if (std::string token; getNextToken(token))
        {
            try
            {
                return std::stod(token);
            }
            catch (const std::exception&)
            {
                throw std::runtime_error("Failed to parse double: " + token);
            }
        }
        throw std::runtime_error("No more doubles available.");
    }

    inline auto Scanner::nextLine() const -> std::string
    {
        std::string line;
        std::getline(input_, line);
        return line;
    }

    inline auto Scanner::getNextToken(std::string& token) const -> bool
    {
        // Skip leading whitespace
        while (input_.peek() != EOF && std::isspace(input_.peek()))
        {
            input_.get();
        }

        if (input_.peek() == EOF)
        {
            return false;
        }

        // Read until next whitespace
        token.clear();
        while (input_.peek() != EOF && !std::isspace(input_.peek()))
        {
            token += static_cast<char>(input_.get());
        }
        return true;
    }

    inline auto Scanner::nextTokens(const char delimiter) const -> std::vector<std::string>
    {
        std::string line;
        std::getline(input_, line);
        std::vector<std::string> tokens;
        boost::split(tokens, line, boost::is_any_of(std::string(1, delimiter)));

        // Remove empty tokens
        std::erase_if(tokens,
                      [](const std::string& s) { return s.empty(); });
        return tokens;
    }
}
