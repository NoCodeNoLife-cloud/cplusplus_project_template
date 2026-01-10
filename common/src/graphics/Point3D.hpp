#pragma once
#include <iostream>

namespace common
{
    /// @brief A 3D point class
    /// @details This class represents a point in 3D space with x, y and z coordinates.
    ///          It provides basic operations such as addition, subtraction, and comparison.
    class Point3D
    {
    public:
        Point3D() noexcept;

        Point3D(double x, double y, double z) noexcept;

        /// @brief Get the X coordinate
        /// @return X coordinate value
        [[nodiscard]] auto getX() const noexcept -> double;

        /// @brief Get the Y coordinate
        /// @return Y coordinate value
        [[nodiscard]] auto getY() const noexcept -> double;
        
        /// @brief Get the Z coordinate
        /// @return Z coordinate value
        [[nodiscard]] auto getZ() const noexcept -> double;

        /// @brief Set the X coordinate
        /// @param x X coordinate value
        auto setX(double x) noexcept -> void;

        /// @brief Set the Y coordinate
        /// @param y Y coordinate value
        auto setY(double y) noexcept -> void;
        
        /// @brief Set the Z coordinate
        /// @param z Z coordinate value
        auto setZ(double z) noexcept -> void;

        /// @brief Add another Point3D to this point
        /// @param other Point3D to add
        /// @return Reference to this point
        auto operator+=(const Point3D& other) noexcept -> Point3D&;

        /// @brief Subtract another Point3D from this point
        /// @param other Point3D to subtract
        /// @return Reference to this point
        auto operator-=(const Point3D& other) noexcept -> Point3D&;

        /// @brief Negate this point
        /// @return Negated point
        [[nodiscard]] auto operator-() const noexcept -> Point3D;

        // Friend operators
        friend auto operator+(Point3D lhs, const Point3D& rhs) noexcept -> Point3D;

        friend auto operator-(Point3D lhs, const Point3D& rhs) noexcept -> Point3D;

        friend auto operator==(const Point3D& lhs, const Point3D& rhs) noexcept -> bool;

        friend auto operator!=(const Point3D& lhs, const Point3D& rhs) noexcept -> bool;

        friend auto operator<<(std::ostream& os, const Point3D& point) -> std::ostream&;

    private:
        double x_{0.0};
        double y_{0.0};
        double z_{0.0};
    };
}