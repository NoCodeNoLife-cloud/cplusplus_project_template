#pragma once
#include <cmath>

namespace fox
{
    /// @brief A class representing a point in 3D space.
    /// The class provides basic functionality for working with points in three-dimensional space,
    /// including setting and getting coordinates, and calculating distances between points.
    class Point3D
    {
    public:
        Point3D() noexcept;

        Point3D(double xVal, double yVal, double zVal) noexcept;

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
        /// @param xVal New X coordinate value
        auto setX(double xVal) noexcept -> void;

        /// @brief Set the Y coordinate
        /// @param yVal New Y coordinate value
        auto setY(double yVal) noexcept -> void;

        /// @brief Set the Z coordinate
        /// @param zVal New Z coordinate value
        auto setZ(double zVal) noexcept -> void;

        /// @brief Calculate distance to another point
        /// @param other The other point to calculate distance to
        /// @return Distance to the other point
        [[nodiscard]] auto distanceTo(const Point3D& other) const noexcept -> double;

    private:
        double x_{0.0};
        double y_{0.0};
        double z_{0.0};
    };

    inline Point3D::Point3D() noexcept = default;

    inline Point3D::Point3D(const double xVal, const double yVal, const double zVal) noexcept : x_(xVal), y_(yVal),
        z_(zVal)
    {
    }

    inline auto Point3D::getX() const noexcept -> double
    {
        return x_;
    }

    inline auto Point3D::getY() const noexcept -> double
    {
        return y_;
    }

    inline auto Point3D::getZ() const noexcept -> double
    {
        return z_;
    }

    inline auto Point3D::setX(const double xVal) noexcept -> void
    {
        x_ = xVal;
    }

    inline auto Point3D::setY(const double yVal) noexcept -> void
    {
        y_ = yVal;
    }

    inline auto Point3D::setZ(const double zVal) noexcept -> void
    {
        z_ = zVal;
    }

    inline auto Point3D::distanceTo(const Point3D& other) const noexcept -> double
    {
        const double dx = x_ - other.x_;
        const double dy = y_ - other.y_;
        const double dz = z_ - other.z_;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
}
