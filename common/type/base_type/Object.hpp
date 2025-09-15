#pragma once
#include <format>
#include <typeinfo>

namespace fox
{
    /// @brief Base class for all objects in the system.
    /// @details This class provides basic functionality for type information, hashing, and string representation.
    /// It is designed to be inherited by other classes that need these features.
    class Object
    {
    public:
        virtual ~Object() = default;

        /// @brief Get the type information of the object.
        /// @return const std::type_info& The type information.
        [[nodiscard]] virtual auto getClass() const -> const std::type_info&
        {
            return typeid(*this);
        }

        /// @brief Get the hash code of the object.
        /// @return size_t The hash code.
        [[nodiscard]] virtual auto hashCode() const -> size_t
        {
            constexpr size_t seed = 0;
            return seed;
        }

    private:
        friend std::formatter<Object>;
    };
} // namespace fox
