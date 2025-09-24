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
        virtual ~Object();

        /// @brief Get the type information of the object.
        /// @return const std::type_info& The type information.
        [[nodiscard]] virtual auto getClass() const noexcept -> const std::type_info&;

        /// @brief Get the hash code of the object.
        /// @return size_t The hash code.
        [[nodiscard]] virtual auto hashCode() const noexcept -> size_t;

    private:
        friend std::formatter<Object>;
    };

    inline Object::~Object() = default;

    inline auto Object::getClass() const noexcept -> const std::type_info&
    {
        return typeid(*this);
    }

    inline auto Object::hashCode() const noexcept -> size_t
    {
        return 0;
    }
}
