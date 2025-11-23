#pragma once
#include <format>
#include <typeinfo>

namespace common
{
    /// @brief Base class for all objects in the system.
    /// @details This class provides basic functionality for type information, hashing, and string representation.
    /// It is designed to be inherited by other classes that need these features.
    // ReSharper disable once CppClassCanBeFinal
    class Object
    {
    public:
        virtual ~Object() = default;

        /// @brief Get the type information of the object.
        /// @return const std::type_info& The type information.
        [[nodiscard]] virtual auto getClass() const noexcept
            -> const std::type_info&;

        /// @brief Compares this object with another object for equality.
        /// @param other The object to compare with.
        /// @return true if the objects are equal, false otherwise.
        /// @details By default, this implementation compares the memory addresses of the objects.
        /// Derived classes should override this method to provide meaningful equality comparison.
        [[nodiscard]] virtual auto equals(const Object& other) const
            -> bool;

        /// @brief Get the hash code of the object.
        /// @return size_t The hash code.
        /// @details This method should be overridden by derived classes to provide a meaningful hash
        /// based on the object's content. The default implementation returns the memory address hash.
        [[nodiscard]] virtual auto hashCode() const noexcept
            -> size_t;

        /// @brief Returns a string representation of the object.
        /// @return std::string representation of the object.
        /// @details This method should be overridden by derived classes to provide a meaningful string
        /// representation of the object's content. The default implementation returns the type name.
        [[nodiscard]] virtual auto toString() const
            -> std::string = 0;

    private:
        friend std::formatter<Object>;
    };
}
