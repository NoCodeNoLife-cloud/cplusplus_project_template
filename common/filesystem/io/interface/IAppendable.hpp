#pragma once
#include <string>
#include <string_view>
#include <initializer_list>

namespace fox
{
    /// @brief Interface for appendable objects.
    /// This interface provides methods for appending characters and strings to objects.
    /// @tparam T The type of the object that implements this interface.
    template <typename T>
    class IAppendable
    {
    public:
        /// @brief Virtual destructor for proper cleanup of derived classes
        virtual ~IAppendable() = default;

        /// @brief Append a character to the object
        /// @param c The character to append
        /// @return A reference to the object for method chaining
        virtual auto append(char c) -> T& = 0;

        /// @brief Append a string to the object
        /// @param str The string to append
        /// @return A reference to the object for method chaining
        virtual auto append(const std::string& str) -> T& = 0;

        /// @brief Append a substring to the object
        /// @param str The string to append
        /// @param start The start index of the substring (inclusive)
        /// @param end The end index of the substring (exclusive)
        /// @return A reference to the object for method chaining
        virtual auto append(const std::string& str, size_t start, size_t end) -> T& = 0;

        /// @brief Append a string view to the object
        /// @param str The string view to append
        /// @return A reference to the object for method chaining
        virtual auto append(std::string_view str) -> T& = 0;

        /// @brief Append a C-style string to the object
        /// @param str The C-style string to append
        /// @return A reference to the object for method chaining
        virtual auto append(const char* str) -> T& = 0;

        /// @brief Append characters from an initializer list to the object
        /// @param chars The characters to append
        /// @return A reference to the object for method chaining
        virtual auto append(std::initializer_list<char> chars) -> T& = 0;
    };
}
